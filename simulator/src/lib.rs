pub mod sim_hal;
pub mod input_scenario;
pub mod test_scenarios;
pub mod benchmark;
pub mod integration_tests;
pub mod core_integration;

pub use sim_hal::{SimKeyboard, SimTimer};
pub use input_scenario::{example_scenario, KeyEvent};
pub use keyboard_core::{KeyboardHW, KeyEventHandler, Timer};
pub use std::env;

fn get_algorithm_name() -> &'static str {
    #[cfg(feature = "no-debounce")]
    { "no-debounce" }
    #[cfg(feature = "time-debounce")]
    { "time-debounce" }
    #[cfg(feature = "mask-debounce")]
    { "mask-debounce" }
    #[cfg(not(any(feature = "no-debounce", feature = "time-debounce", feature = "mask-debounce")))]
    { "unknown" }
}

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

pub fn print_usage() {
    let algorithm_name = get_algorithm_name();
    println!("LLMK Keyboard Simulator ({})", algorithm_name);
    println!("A platform-agnostic keyboard simulation and testing framework");
    println!();
    println!("Usage: simulator <command> [options]");
    println!();
    println!("Commands:");
    println!("  run <scenario>               Run simulator with specific scenario");
    println!("  benchmark [scenario]         Run performance benchmarks");
    println!("  test                         Run integration test suite");
    println!("  list-scenarios               List available test scenarios");
    println!("  memory                       Analyze memory usage of debounce algorithms");
    println!("  legacy                       Run original simulator implementation");
    println!();
    println!("Examples:");
    println!("  simulator run bouncy");
    println!("  simulator benchmark rapid_fire");
    println!("  simulator test");
    println!();
    println!("Debounce algorithm: {} (selected at compile time)", algorithm_name);
    println!("Use --features to select: no-debounce, time-debounce, or mask-debounce");
}

pub fn list_scenarios_cmd() {
    println!("Available scenarios:");
    for scenario in test_scenarios::list_scenarios() {
        println!("  {}", scenario);
    }
}

pub fn run_simulator_with_scenario(scenario_name: &str) {
    let events = match test_scenarios::get_scenario_by_name(scenario_name) {
        Some(events) => events,
        None => {
            println!("Unknown scenario: {}. Use 'list-scenarios' to see available options.", scenario_name);
            return;
        }
    };

    // This will be implemented by each binary with its specific debounce algorithm
    run_enhanced_simulator(events, scenario_name);
}

pub fn run_benchmarks_cmd(scenario_filter: Option<&String>) {
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

    // This will be implemented by each binary with its specific debounce algorithm
    run_benchmarks_for_algorithm(scenarios);
    benchmark::benchmark_memory_usage();
}

pub fn run_integration_tests_cmd() {
    // This will be implemented by each binary with its specific debounce algorithm
    run_integration_tests_for_algorithm();
}

pub fn run_legacy_simulator() {
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

// These functions provide compile-time algorithm selection using the ActiveDebouncer
pub fn run_enhanced_simulator(events: Vec<KeyEvent>, scenario_name: &str) {
    use keyboard_core::ActiveDebouncer;
    
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let mut handler = SimEventHandler::new();
    let mut debouncer = ActiveDebouncer::default();

    let algorithm_name = get_algorithm_name();
    println!("Starting enhanced simulation: {} with {}", scenario_name, algorithm_name);
    
    let max_time = events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 20;
    let mut event_idx = 0;

    run_enhanced_simulation_with_debouncer(&mut hw, &mut timer, &mut handler, &mut debouncer,
                                         &events, max_time, &mut event_idx);

    println!("✅ Enhanced simulation complete.");
    println!("Key events generated: {}", handler.events.len());
    
    if !handler.events.is_empty() {
        println!("Event summary:");
        for (timestamp, key, pressed) in handler.get_last_events(10) {
            println!("  [{}] Key {} {}", timestamp, key, if *pressed { "↓" } else { "↑" });
        }
    }
}

pub fn run_benchmarks_for_algorithm(scenarios: Vec<(&str, Vec<KeyEvent>)>) {
    let algorithm_name = get_algorithm_name();
    println!("Starting benchmark suite with {}...", algorithm_name);
    
    let mut results = Vec::new();
    for (scenario_name, events) in scenarios {
        println!("Benchmarking {} with {}...", scenario_name, algorithm_name);
        
        let result = benchmark::benchmark_scenario(
            scenario_name.to_string(),
            events,
            algorithm_name.to_string(),
        );
        
        result.print();
        results.push(result);
    }
}

pub fn run_integration_tests_for_algorithm() {
    let algorithm_name = get_algorithm_name();
    let test_cases = integration_tests::create_debounce_tests();
    let mut results = Vec::new();

    println!("Running integration tests with {}...", algorithm_name);
    
    for test_case in &test_cases {
        let result = integration_tests::run_integration_test(test_case, algorithm_name);
        result.print();
        results.push(result);
    }

    // Print summary
    let total_tests = results.len();
    let passed_tests = results.iter().filter(|r| r.passed).count();
    
    println!("\n=== Test Summary ===");
    println!("Algorithm: {}", algorithm_name);
    println!("Passed: {}/{}", passed_tests, total_tests);
    println!("Failed: {}/{}", total_tests - passed_tests, total_tests);
    println!("==================");
}

fn run_enhanced_simulation_with_debouncer<D>(
    hw: &mut SimKeyboard,
    timer: &mut SimTimer,
    handler: &mut SimEventHandler,
    debouncer: &mut D,
    events: &[KeyEvent],
    max_time: u64,
    event_idx: &mut usize,
) where
    D: keyboard_core::Debouncer,
{
    use keyboard_core::{Timer, KeyEventHandler};
    
    const NUM_ROWS: usize = 4;
    const NUM_COLS: usize = 8; 
    const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;

    let mut tick_ms = 0;

    while tick_ms <= max_time {
        // Apply input events
        while *event_idx < events.len() && events[*event_idx].time_ms == tick_ms {
            let ev = &events[*event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            println!(
                "[{} ms] Key {}:{} {}",
                tick_ms,
                ev.row,
                ev.col,
                if ev.pressed { "pressed" } else { "released" }
            );
            *event_idx += 1;
        }

        // Matrix scanning with real debounce logic
        let mut raw_state = 0u64;
        for row in 0..NUM_ROWS {
            hw.set_row_active(row);
            let val = hw.read_keys();
            if val != 0 {
                println!("[{} ms] Row {} scan: {:016b}", tick_ms, row, val);
            }
            for col in 0..NUM_COLS {
                if (val >> col) & 1 != 0 {
                    let idx = row * NUM_COLS + col;
                    raw_state |= 1u64 << idx;
                }
            }
        }
        hw.set_all_rows_inactive();

        // Debounce processing
        let (_, pressed, released) = debouncer.update(raw_state, timer.millis());
        
        // Generate key events
        for i in 0..NUM_KEYS {
            let mask = 1u64 << i;
            if pressed & mask != 0 {
                handler.key_event(i, true);
            }
            if released & mask != 0 {
                handler.key_event(i, false);
            }
        }
        
        timer.advance(1);
        tick_ms += 1;
    }
}