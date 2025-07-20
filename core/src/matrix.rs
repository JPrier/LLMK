use crate::{ActiveDebouncer, Debouncer, KeyEventHandler, KeyboardHW, Timer};
const NUM_ROWS: usize = 4;
const NUM_COLS: usize = 8;
const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;
pub fn process<H, T, E>(hw: &mut H, timer: &T, handler: &mut E)
where
    H: KeyboardHW,
    T: Timer,
    E: KeyEventHandler,
{
    let mut debouncer = ActiveDebouncer::default();
    loop {
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

        let (state, pressed, released) = debouncer.update(raw_state, timer.millis());
        let _ = state;
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
}
