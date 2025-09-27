mod sim_hal;
mod input_scenario;
mod test_scenarios;
mod benchmark;
mod integration_tests;

use sim_hal::{SimKeyboard, SimTimer};
use input_scenario::{example_scenario, KeyEvent};
use keyboard_core::{KeyboardHW, KeyEventHandler};
use std::env;

pub struct SimEventHandler {
    pub events: Vec<(u64, usize, bool)>, // (timestamp, key_index, pressed)
}

impl SimEventHandler {
    pub fn new() -> Self {
        Self {
            events: Vec::new(),
        }
    }
    
    pub fn get_last_events(&self, count: usize) -> &[(u64, usize, bool)] {
        let start = self.events.len().saturating_sub(count);
        &self.events[start..]
    }
}

impl KeyEventHandler for SimEventHandler {
    fn key_event(&mut self, key: usize, pressed: bool) {
        // In a real application, this would be the current timestamp
        // For simulation, we'll store the events for validation
        let timestamp = self.events.len() as u64; // Simple monotonic counter
        self.events.push((timestamp, key, pressed));
        println!("[SIM] Key {} {}", key, if pressed { "pressed" } else { "released" });
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() < 2 {
        print_usage();
        return;
    }
    
    match args[1].as_str() {
        "run" => {
            let default_scenario = "example".to_string();
            let default_debounce = "time-debounce".to_string();
            let scenario_name = args.get(2).unwrap_or(&default_scenario);
            let debounce_alg = args.get(3).unwrap_or(&default_debounce);
            run_simulator_with_scenario(scenario_name, debounce_alg);
        },
        "benchmark" => {
            let scenario_filter = args.get(2);
            run_benchmarks_cmd(scenario_filter);
        },
        "test" => {
            run_integration_tests_cmd();
        },
        "list-scenarios" => {
            list_scenarios_cmd();
        },
        "memory" => {
            benchmark::benchmark_memory_usage();
        },
        "legacy" => {
            // Run the original simulator for comparison
            run_legacy_simulator();
        },
        _ => {
            println!("Unknown command: {}", args[1]);
            print_usage();
        }
    }
}

fn print_usage() {
    println!("LLMK Keyboard Simulator");
    println!("A platform-agnostic keyboard simulation and testing framework");
    println!();
    println!("Usage: simulator <command> [options]");
    println!();
    println!("Commands:");
    println!("  run <scenario> [debounce]    Run simulator with specific scenario");
    println!("                               debounce: no-debounce, time-debounce, mask-debounce");
    println!("  benchmark [scenario]         Run performance benchmarks");
    println!("  test                         Run integration test suite");
    println!("  list-scenarios               List available test scenarios");
    println!("  memory                       Analyze memory usage of debounce algorithms");
    println!("  legacy                       Run original simulator implementation");
    println!();
    println!("Examples:");
    println!("  simulator run bouncy time-debounce");
    println!("  simulator benchmark rapid_fire");
    println!("  simulator test");
}

fn list_scenarios_cmd() {
    println!("Available scenarios:");
    for scenario in test_scenarios::list_scenarios() {
        println!("  {}", scenario);
    }
}

fn run_simulator_with_scenario(scenario_name: &str, debounce_alg: &str) {
    println!("Running simulator with scenario: {} (debounce: {})", scenario_name, debounce_alg);
    
    let events = match test_scenarios::get_scenario_by_name(scenario_name) {
        Some(events) => events,
        None => {
            println!("Unknown scenario: {}. Use 'list-scenarios' to see available options.", scenario_name);
            return;
        }
    };

    // For now, run the enhanced version of the legacy simulator
    // TODO: Integrate with actual keyboard_core logic
    run_enhanced_simulator(events, scenario_name, debounce_alg);
}

fn run_benchmarks_cmd(scenario_filter: Option<&String>) {
    let scenarios: Vec<(&str, Vec<KeyEvent>)> = if let Some(filter) = scenario_filter {
        match test_scenarios::get_scenario_by_name(filter) {
            Some(events) => vec![(filter, events)],
            None => {
                println!("Unknown scenario: {}", filter);
                return;
            }
        }
    } else {
        // Run all scenarios
        test_scenarios::list_scenarios()
            .into_iter()
            .filter_map(|name| {
                test_scenarios::get_scenario_by_name(name)
                    .map(|events| (name, events))
            })
            .collect()
    };

    let _results = benchmark::run_benchmarks(scenarios);
    benchmark::benchmark_memory_usage();
}

fn run_integration_tests_cmd() {
    let _results = integration_tests::run_integration_tests();
}

fn run_enhanced_simulator(events: Vec<KeyEvent>, scenario_name: &str, debounce_alg: &str) {
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let handler = SimEventHandler::new();

    println!("Starting enhanced simulation: {} with {}", scenario_name, debounce_alg);
    
    let max_time = events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 20;
    let mut tick_ms = 0;
    let mut event_idx = 0;

    while tick_ms <= max_time {
        // Apply input events
        while event_idx < events.len() && events[event_idx].time_ms == tick_ms {
            let ev = &events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            println!(
                "[{} ms] Key {}:{} {}",
                tick_ms,
                ev.row,
                ev.col,
                if ev.pressed { "pressed" } else { "released" }
            );
            event_idx += 1;
        }

        // Simulate matrix scanning with improved output
        hw.set_all_rows_inactive();
        for row in 0..4 {
            hw.set_row_active(row);
            let keys = hw.read_keys();
            if keys != 0 {
                println!("[{} ms] Row {} scan: {:016b}", tick_ms, row, keys);
            }
        }

        timer.advance(1);
        tick_ms += 1;
    }

    println!("✅ Enhanced simulation complete.");
    println!("Key events generated: {}", handler.events.len());
    
    if !handler.events.is_empty() {
        println!("Event summary:");
        for (timestamp, key, pressed) in handler.get_last_events(10) {
            println!("  [{}] Key {} {}", timestamp, key, if *pressed { "↓" } else { "↑" });
        }
    }
}

fn run_legacy_simulator() {
    println!("Running legacy simulator for comparison...");
    
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let events = example_scenario();

    let max_time = events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 20;
    let mut tick_ms = 0;
    let mut event_idx = 0;

    while tick_ms <= max_time {
        while event_idx < events.len() && events[event_idx].time_ms == tick_ms {
            let ev = &events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            println!(
                "[{} ms] Key {}:{} {}",
                tick_ms,
                ev.row,
                ev.col,
                if ev.pressed { "pressed" } else { "released" }
            );
            event_idx += 1;
        }

        hw.set_all_rows_inactive();

        for row in 0..4 {
            hw.set_row_active(row);
            let keys = hw.read_keys();
            if keys != 0 {
                println!("[{} ms] Keys: {:064b}", tick_ms, keys);
            }
        }

        timer.advance(1);
        tick_ms += 1;
    }

    println!("✅ Legacy simulation complete.");
}
