pub struct KeyEvent {
    pub time_ms: u64,
    pub row: usize,
    pub col: usize,
    pub pressed: bool,
}

pub fn example_scenario() -> Vec<KeyEvent> {
    vec![
        KeyEvent {
            time_ms: 10,
            row: 0,
            col: 0,
            pressed: true,
        },
        KeyEvent {
            time_ms: 13,
            row: 0,
            col: 0,
            pressed: false,
        },
        KeyEvent {
            time_ms: 16,
            row: 0,
            col: 0,
            pressed: true,
        },
        KeyEvent {
            time_ms: 50,
            row: 0,
            col: 0,
            pressed: false,
        },
        KeyEvent {
            time_ms: 60,
            row: 1,
            col: 1,
            pressed: true,
        },
    ]
}
