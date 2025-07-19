pub struct KeyEvent {
    pub time_ms: u64,
    pub row: usize,
    pub col: usize,
    pub pressed: bool,
}

pub fn example_scenario() -> Vec<KeyEvent> {
    vec![
        KeyEvent { time_ms: 10, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 13, row: 0, col: 0, pressed: false }, // bounce
        KeyEvent { time_ms: 16, row: 0, col: 0, pressed: true },
        KeyEvent { time_ms: 50, row: 0, col: 0, pressed: false },
    ]
}
