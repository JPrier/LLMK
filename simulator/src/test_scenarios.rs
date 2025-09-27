use crate::KeyEvent;

pub fn rapid_fire_scenario() -> Vec<KeyEvent> {
    let mut events = Vec::new();
    
    // Rapid key presses on the same key to test debouncing
    for i in 0..10 {
        let time = i * 2; // Every 2ms
        events.push(KeyEvent { time_ms: time, row: 0, col: 0, pressed: true });
        events.push(KeyEvent { time_ms: time + 1, row: 0, col: 0, pressed: false });
    }
    
    events
}

pub fn simultaneous_keys_scenario() -> Vec<KeyEvent> {
    vec![
        // Press multiple keys at once
        KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 10, row: 0, col: 1, pressed: true },
        KeyEvent { time_ms: 10, row: 1, col: 0, pressed: true },
        KeyEvent { time_ms: 10, row: 1, col: 1, pressed: true },
        
        // Release them at different times
        KeyEvent { time_ms: 50, row: 0, col: 0, pressed: false },
        KeyEvent { time_ms: 60, row: 0, col: 1, pressed: false },
        KeyEvent { time_ms: 70, row: 1, col: 0, pressed: false },
        KeyEvent { time_ms: 80, row: 1, col: 1, pressed: false },
    ]
}

pub fn bouncy_key_scenario() -> Vec<KeyEvent> {
    vec![
        // Simulate a bouncy key that rapidly switches state
        KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 11, row: 0, col: 0, pressed: false },
        KeyEvent { time_ms: 12, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 13, row: 0, col: 0, pressed: false },
        KeyEvent { time_ms: 14, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 15, row: 0, col: 0, pressed: false },
        KeyEvent { time_ms: 16, row: 0, col: 0, pressed: true },
        
        // Then stable
        KeyEvent { time_ms: 100, row: 0, col: 0, pressed: false },
    ]
}

pub fn long_press_scenario() -> Vec<KeyEvent> {
    vec![
        KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
        // Hold for 1 second
        KeyEvent { time_ms: 1010, row: 0, col: 0, pressed: false },
    ]
}

pub fn all_keys_scenario() -> Vec<KeyEvent> {
    let mut events = Vec::new();
    
    // Press all keys in matrix order
    for row in 0..4 {
        for col in 0..4 {
            let time = (row * 4 + col) as u64 * 10;
            events.push(KeyEvent { time_ms: time, row, col, pressed: true });
            events.push(KeyEvent { time_ms: time + 50, row, col, pressed: false });
        }
    }
    
    events
}

pub fn get_scenario_by_name(name: &str) -> Option<Vec<KeyEvent>> {
    match name {
        "rapid_fire" => Some(rapid_fire_scenario()),
        "simultaneous" => Some(simultaneous_keys_scenario()),
        "bouncy" => Some(bouncy_key_scenario()),
        "long_press" => Some(long_press_scenario()),
        "all_keys" => Some(all_keys_scenario()),
        "example" => Some(crate::example_scenario()),
        _ => None,
    }
}

pub fn list_scenarios() -> Vec<&'static str> {
    vec![
        "example",
        "rapid_fire",
        "simultaneous", 
        "bouncy",
        "long_press",
        "all_keys"
    ]
}