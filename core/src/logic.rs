use crate::{KeyboardHW, Timer, KeyEventHandler, KeyState};

const NUM_ROWS: usize = 4;
const NUM_COLS: usize = 8;
const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;
const DEBOUNCE_BITS: u8 = 5;
const MASK: u16 = (1 << DEBOUNCE_BITS) - 1;

pub struct KeyboardLogic {
    history: [u16; NUM_KEYS],
    stable: KeyState,
}

impl Default for KeyboardLogic {
    fn default() -> Self {
        Self::new()
    }
}

impl KeyboardLogic {
    pub fn new() -> Self {
        Self {
            history: [0u16; NUM_KEYS],
            stable: 0,
        }
    }

    pub fn poll<H, T, E>(&mut self, hw: &mut H, timer: &T, handler: &mut E)
    where
        H: KeyboardHW,
        T: Timer,
        E: KeyEventHandler,
    {
        for row in 0..NUM_ROWS {
            hw.set_row_active(row);
            let val = hw.read_keys();
            for col in 0..NUM_COLS {
                let idx = row * NUM_COLS + col;
                let bit = ((val >> idx) & 1) as u16;
                self.history[idx] = ((self.history[idx] << 1) | bit) & MASK;
                let cur = (self.stable >> idx) & 1;
                if self.history[idx] == MASK && cur == 0 {
                    self.stable |= 1u64 << idx;
                    handler.key_event(idx, true);
                } else if self.history[idx] == 0 && cur == 1 {
                    self.stable &= !(1u64 << idx);
                    handler.key_event(idx, false);
                }
            }
        }
        hw.set_all_rows_inactive();
        let _ = timer.millis();
    }
}
