use crate::{KeyEventHandler, KeyState, KeyboardHW, Timer};
const NUM_ROWS: usize = 4;
const NUM_COLS: usize = 8;
const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;
const DEBOUNCE_BITS: u8 = 5;
const MASK: u16 = (1 << DEBOUNCE_BITS) - 1;
pub fn process<H, T, E>(hw: &mut H, timer: &T, handler: &mut E)
where
    H: KeyboardHW,
    T: Timer,
    E: KeyEventHandler,
{
    let mut history = [0u16; NUM_KEYS];
    let mut stable: KeyState = 0;
    loop {
        for row in 0..NUM_ROWS {
            hw.set_row_active(row);
            let val = hw.read_keys();
            for col in 0..NUM_COLS {
                let idx = row * NUM_COLS + col;
                let bit = ((val >> col) & 1) as u16;
                history[idx] = ((history[idx] << 1) | bit) & MASK;
                let cur = (stable >> idx) & 1;
                if history[idx] == MASK && cur == 0 {
                    stable |= 1u64 << idx;
                    handler.key_event(idx, true);
                } else if history[idx] == 0 && cur == 1 {
                    stable &= !(1u64 << idx);
                    handler.key_event(idx, false);
                }
            }
        }
        hw.set_all_rows_inactive();
        let _ = timer.millis();
    }
}
