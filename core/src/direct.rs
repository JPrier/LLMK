use crate::{KeyEventHandler, KeyState, KeyboardHW, Timer};

const NUM_KEYS: usize = 32;
const DEBOUNCE_BITS: u8 = 5;
const MASK: u16 = (1 << DEBOUNCE_BITS) - 1;

pub fn process<H, T, E>(hw: &mut H, timer: &T, handler: &mut E)
where
    H: KeyboardHW,
    T: Timer,
    E: KeyEventHandler,
{
    let mut history = [0u16; NUM_KEYS];
    let mut stable: KeyState = hw.read_keys();
    loop {
        let raw = hw.read_keys();
        for i in 0..NUM_KEYS {
            let bit = ((raw >> i) & 1) as u16;
            history[i] = ((history[i] << 1) | bit) & MASK;
            let cur = (stable >> i) & 1;
            if history[i] == MASK && cur == 0 {
                stable |= 1u64 << i;
                handler.key_event(i, true);
            } else if history[i] == 0 && cur == 1 {
                stable &= !(1u64 << i);
                handler.key_event(i, false);
            }
        }
        let _ = timer.millis();
    }
}
