use crate::{SimEventHandler, SimKeyboard, SimTimer};
use crate::input_scenario::KeyEvent;
use keyboard_core::KeyboardHW;

#[derive(Debug, Clone)]
pub struct TestCase {
    pub name: String,
    pub description: String,
    pub input_events: Vec<KeyEvent>,
    pub expected_outputs: Vec<(usize, bool)>, // (key_index, pressed)
}

pub struct TestResult {
    pub test_name: String,
    pub passed: bool,
    pub message: String,
    pub actual_events: Vec<(usize, bool)>,
    pub expected_events: Vec<(usize, bool)>,
}

impl TestResult {
    pub fn print(&self) {
        let status = if self.passed { "PASS" } else { "FAIL" };
        println!("[{}] {}: {}", status, self.test_name, self.message);
        
        if !self.passed {
            println!("  Expected: {:?}", self.expected_events);
            println!("  Actual:   {:?}", self.actual_events);
        }
    }
}

pub fn create_debounce_tests() -> Vec<TestCase> {
    vec![
        TestCase {
            name: "basic_key_press".to_string(),
            description: "Single key press and release should generate exactly two events".to_string(),
            input_events: vec![
                KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 50, row: 0, col: 0, pressed: false },
            ],
            expected_outputs: vec![
                (0, true),   // key 0 pressed
                (0, false),  // key 0 released
            ],
        },
        
        TestCase {
            name: "bounce_rejection".to_string(),
            description: "Bouncy input should be debounced to single press/release".to_string(),
            input_events: vec![
                KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 11, row: 0, col: 0, pressed: false },
                KeyEvent { time_ms: 12, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 13, row: 0, col: 0, pressed: false },
                KeyEvent { time_ms: 14, row: 0, col: 0, pressed: true },
                // Final stable state after debounce period
                KeyEvent { time_ms: 100, row: 0, col: 0, pressed: false },
            ],
            expected_outputs: vec![
                (0, true),   // Initial press (after debounce)
                (0, false),  // Final release (after debounce)
            ],
        },
        
        TestCase {
            name: "simultaneous_keys".to_string(),
            description: "Multiple keys pressed simultaneously should all register".to_string(),
            input_events: vec![
                KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 10, row: 0, col: 1, pressed: true },
                KeyEvent { time_ms: 10, row: 1, col: 0, pressed: true },
                KeyEvent { time_ms: 50, row: 0, col: 0, pressed: false },
                KeyEvent { time_ms: 50, row: 0, col: 1, pressed: false },
                KeyEvent { time_ms: 50, row: 1, col: 0, pressed: false },
            ],
            expected_outputs: vec![
                (0, true),   // key 0 pressed
                (1, true),   // key 1 pressed  
                (4, true),   // key 4 pressed (row 1, col 0)
                (0, false),  // key 0 released
                (1, false),  // key 1 released
                (4, false),  // key 4 released
            ],
        },
        
        TestCase {
            name: "rapid_succession".to_string(),
            description: "Rapid key presses should be handled correctly".to_string(),
            input_events: vec![
                KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 30, row: 0, col: 0, pressed: false },
                KeyEvent { time_ms: 50, row: 0, col: 0, pressed: true },
                KeyEvent { time_ms: 70, row: 0, col: 0, pressed: false },
            ],
            expected_outputs: vec![
                (0, true),   // First press
                (0, false),  // First release
                (0, true),   // Second press
                (0, false),  // Second release
            ],
        },
    ]
}

pub fn run_integration_test(test_case: &TestCase, _debounce_algorithm: &str) -> TestResult {
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let handler = SimEventHandler::new();

    let max_time = test_case.input_events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 50;
    
    let mut tick_ms = 0;
    let mut event_idx = 0;

    // Run the simulation
    while tick_ms <= max_time {
        // Apply input events
        while event_idx < test_case.input_events.len() 
            && test_case.input_events[event_idx].time_ms == tick_ms {
            let ev = &test_case.input_events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            event_idx += 1;
        }

        // Process matrix scan
        hw.set_all_rows_inactive();
        for row in 0..4 {
            hw.set_row_active(row);
            let _keys = hw.read_keys();
            
            // For now, we simulate the debounce logic
            // In a complete implementation, this would call keyboard_core::run()
        }
        
        timer.advance(1);
        tick_ms += 1;
    }

    // For now, we'll simulate expected behavior since we're not yet calling
    // the full core logic. This is a placeholder that needs the actual 
    // keyboard_core integration.
    let actual_events: Vec<(usize, bool)> = handler.events.iter()
        .map(|(_, key, pressed)| (*key, *pressed))
        .collect();

    // Simple comparison - in reality this would be more sophisticated
    let passed = actual_events.len() == test_case.expected_outputs.len();
    
    let message = if passed {
        "Test passed".to_string()
    } else {
        format!("Expected {} events, got {}", test_case.expected_outputs.len(), actual_events.len())
    };

    TestResult {
        test_name: test_case.name.clone(),
        passed,
        message,
        actual_events,
        expected_events: test_case.expected_outputs.clone(),
    }
}

pub fn run_integration_tests() -> Vec<TestResult> {
    let test_cases = create_debounce_tests();
    let debounce_algorithms = vec!["no-debounce", "time-debounce", "mask-debounce"];
    let mut results = Vec::new();

    println!("Running integration tests...");
    
    for algorithm in &debounce_algorithms {
        println!("\n--- Testing with {} ---", algorithm);
        
        for test_case in &test_cases {
            let result = run_integration_test(test_case, algorithm);
            result.print();
            results.push(result);
        }
    }

    // Print summary
    let total_tests = results.len();
    let passed_tests = results.iter().filter(|r| r.passed).count();
    
    println!("\n=== Test Summary ===");
    println!("Passed: {}/{}", passed_tests, total_tests);
    println!("Failed: {}/{}", total_tests - passed_tests, total_tests);
    println!("==================");

    results
}