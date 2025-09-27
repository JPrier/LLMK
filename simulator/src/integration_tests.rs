use crate::{SimEventHandler, SimKeyboard, SimTimer};
use crate::input_scenario::KeyEvent;
use keyboard_core::{KeyboardHW, KeyEventHandler, Timer, NoDebounce, TimeDebounce, MaskDebounce, Debouncer};

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

pub fn run_integration_test(test_case: &TestCase, debounce_algorithm: &str) -> TestResult {
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let mut handler = SimEventHandler::new();

    let max_time = test_case.input_events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 50;
    
    let mut event_idx = 0;

    // Apply all input events upfront (they're time-based)
    for tick_ms in 0..=max_time {
        while event_idx < test_case.input_events.len() 
            && test_case.input_events[event_idx].time_ms == tick_ms {
            let ev = &test_case.input_events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            event_idx += 1;
        }

        // Process one tick with the real debounce algorithm
        match debounce_algorithm {
            "no-debounce" => {
                let mut debouncer = NoDebounce::new();
                run_one_simulation_step(&mut hw, &mut timer, &mut handler, &mut debouncer);
            },
            "time-debounce" => {
                let mut debouncer = TimeDebounce::default();
                run_one_simulation_step(&mut hw, &mut timer, &mut handler, &mut debouncer);
            },
            "mask-debounce" => {
                let mut debouncer = MaskDebounce::default();
                run_one_simulation_step(&mut hw, &mut timer, &mut handler, &mut debouncer);
            },
            _ => {
                let mut debouncer = NoDebounce::new();
                run_one_simulation_step(&mut hw, &mut timer, &mut handler, &mut debouncer);
            }
        }
        
        timer.advance(1);
    }

    let actual_events: Vec<(usize, bool)> = handler.events.iter()
        .map(|(_, key, pressed)| (*key, *pressed))
        .collect();

    // Check if we got the expected number of events and they match
    let passed = actual_events.len() == test_case.expected_outputs.len() &&
        actual_events.iter().zip(test_case.expected_outputs.iter())
            .all(|((actual_key, actual_pressed), (expected_key, expected_pressed))| {
                actual_key == expected_key && actual_pressed == expected_pressed
            });
    
    let message = if passed {
        "Test passed".to_string()
    } else if actual_events.len() != test_case.expected_outputs.len() {
        format!("Expected {} events, got {}", test_case.expected_outputs.len(), actual_events.len())
    } else {
        "Event mismatch".to_string()
    };

    TestResult {
        test_name: test_case.name.clone(),
        passed,
        message,
        actual_events,
        expected_events: test_case.expected_outputs.clone(),
    }
}

fn run_one_simulation_step<D>(
    hw: &mut SimKeyboard,
    timer: &mut SimTimer,
    handler: &mut SimEventHandler,
    debouncer: &mut D,
) where
    D: Debouncer,
{
    const NUM_ROWS: usize = 4;
    const NUM_COLS: usize = 8; 
    const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;
    
    // Matrix scanning
    let mut raw_state = 0u64;
    for row in 0..NUM_ROWS {
        hw.set_row_active(row);
        let val = hw.read_keys();
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