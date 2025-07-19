use crate::{KeyState, KeyboardHW, Timer};

const NUM_ROWS: usize = 4;

pub fn process<H: KeyboardHW, T: Timer>(hw: &mut H, timer: &T) {
    let mut stable: [KeyState; NUM_ROWS] = [0; NUM_ROWS];
    loop {
        for row in 0..NUM_ROWS {
            hw.set_row_active(row);
            let val = hw.read_keys();
            stable[row] = val;
        }
        hw.set_all_rows_inactive();
        let _ = timer.millis();
    }
}
