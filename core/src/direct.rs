use crate::{KeyboardHW, Timer};

pub fn process<H: KeyboardHW, T: Timer>(hw: &mut H, timer: &T) {
    let mut last = hw.read_keys();
    loop {
        let now = timer.millis();
        let state = hw.read_keys();
        if state != last {
            // placeholder for event handling in firmware/sim
            last = state;
        }
        let _ = now; // suppress unused variable
    }
}
