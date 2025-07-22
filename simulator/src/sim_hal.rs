use keyboard_core::{KeyboardHW, Timer};

pub struct SimKeyboard {
    pub keys: u64,
    pub active_row: Option<usize>,
    pub num_cols: usize,
}

impl SimKeyboard {
    pub fn new(_rows: usize, cols: usize) -> Self {
        SimKeyboard {
            keys: 0,
            active_row: None,
            num_cols: cols,
        }
    }

    pub fn set_key(&mut self, row: usize, col: usize, pressed: bool) {
        let bit_index = row * self.num_cols + col;
        if pressed {
            self.keys |= 1 << bit_index;
        } else {
            self.keys &= !(1 << bit_index);
        }
    }

    pub fn get_key(&self, row: usize, col: usize) -> bool {
        let bit_index = row * self.num_cols + col;
        (self.keys >> bit_index) & 1 == 1
    }
}

impl KeyboardHW for SimKeyboard {
    fn init(&mut self) {}

    fn read_keys(&self) -> u64 {
        match self.active_row {
            Some(row) => {
                let mut row_keys = 0u64;
                for col in 0..self.num_cols {
                    if self.get_key(row, col) {
                        let bit_index = row * self.num_cols + col;
                        row_keys |= 1 << bit_index;
                    }
                }
                row_keys
            }
            None => 0,
        }
    }

    fn set_row_active(&mut self, row: usize) {
        self.active_row = Some(row);
    }

    fn set_all_rows_inactive(&mut self) {
        self.active_row = None;
    }
}

pub struct SimTimer {
    pub millis: u64,
}

impl SimTimer {
    pub fn new() -> Self {
        Self { millis: 0 }
    }

    pub fn advance(&mut self, delta_ms: u64) {
        self.millis += delta_ms;
    }
}

impl Timer for SimTimer {
    fn millis(&self) -> u64 {
        self.millis
    }
}
