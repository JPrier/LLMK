use crate::{SimEventHandler, SimKeyboard, SimTimer};
use crate::input_scenario::KeyEvent;
use keyboard_core::KeyboardHW;
use std::time::Instant;

pub struct BenchmarkResults {
    pub scenario_name: String,
    pub debounce_algorithm: String,
    pub total_duration_ms: u64,
    pub events_processed: usize,
    pub key_events_generated: usize,
    pub avg_latency_ns: u64,
    pub max_latency_ns: u64,
    pub throughput_events_per_sec: f64,
}

impl BenchmarkResults {
    pub fn print(&self) {
        println!("=== Benchmark Results ===");
        println!("Scenario: {}", self.scenario_name);
        println!("Debounce Algorithm: {}", self.debounce_algorithm);
        println!("Duration: {} ms", self.total_duration_ms);
        println!("Input Events: {}", self.events_processed);
        println!("Key Events Generated: {}", self.key_events_generated);
        println!("Average Latency: {} ns", self.avg_latency_ns);
        println!("Max Latency: {} ns", self.max_latency_ns);
        println!("Throughput: {:.2} events/sec", self.throughput_events_per_sec);
        println!("========================");
    }
}

pub fn benchmark_scenario(
    scenario_name: String,
    events: Vec<KeyEvent>,
    debounce_algorithm: String,
) -> BenchmarkResults {
    let start_time = Instant::now();
    
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let handler = SimEventHandler::new();
    let mut latencies = Vec::new();

    let max_time = events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 20;
    
    let mut tick_ms = 0;
    let mut event_idx = 0;
    let events_processed = events.len();

    while tick_ms <= max_time {
        // Apply input events
        while event_idx < events.len() && events[event_idx].time_ms == tick_ms {
            let ev = &events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            event_idx += 1;
        }

        // Measure processing latency
        let process_start = Instant::now();
        
        // Simulate matrix scanning
        hw.set_all_rows_inactive();
        for row in 0..4 {
            hw.set_row_active(row);
            let _keys = hw.read_keys();
            
            // In a real implementation this would call the debounce logic
            // For now we simulate processing time
        }
        
        let process_duration = process_start.elapsed();
        latencies.push(process_duration.as_nanos() as u64);
        
        timer.advance(1);
        tick_ms += 1;
    }

    let total_duration = start_time.elapsed();
    let key_events_generated = handler.events.len();
    
    let avg_latency_ns = if !latencies.is_empty() {
        latencies.iter().sum::<u64>() / latencies.len() as u64
    } else {
        0
    };
    
    let max_latency_ns = latencies.into_iter().max().unwrap_or(0);
    let throughput = if total_duration.as_secs() > 0 {
        events_processed as f64 / total_duration.as_secs_f64()
    } else {
        events_processed as f64 / (total_duration.as_millis() as f64 / 1000.0)
    };

    BenchmarkResults {
        scenario_name,
        debounce_algorithm,
        total_duration_ms: total_duration.as_millis() as u64,
        events_processed,
        key_events_generated,
        avg_latency_ns,
        max_latency_ns,
        throughput_events_per_sec: throughput,
    }
}

pub fn run_benchmarks(scenarios: Vec<(&str, Vec<KeyEvent>)>) -> Vec<BenchmarkResults> {
    let debounce_algorithms = vec!["time-debounce", "mask-debounce", "no-debounce"];
    let mut results = Vec::new();
    
    println!("Starting benchmark suite...");
    
    for (scenario_name, events) in scenarios {
        for algorithm in &debounce_algorithms {
            println!("Benchmarking {} with {}...", scenario_name, algorithm);
            
            let result = benchmark_scenario(
                scenario_name.to_string(),
                events.clone(),
                algorithm.to_string(),
            );
            
            result.print();
            results.push(result);
        }
    }
    
    results
}

pub fn benchmark_memory_usage() {
    println!("=== Memory Usage Analysis ===");
    
    // Simulate different debounce algorithms memory usage
    use keyboard_core::{NoDebounce, TimeDebounce, MaskDebounce};
    
    let no_debounce_size = std::mem::size_of::<NoDebounce>();
    let time_debounce_size = std::mem::size_of::<TimeDebounce>();
    let mask_debounce_size = std::mem::size_of::<MaskDebounce>();
    
    println!("NoDebounce: {} bytes", no_debounce_size);
    println!("TimeDebounce: {} bytes", time_debounce_size);
    println!("MaskDebounce: {} bytes", mask_debounce_size);
    println!("=============================");
}