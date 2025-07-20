use crate::{ActiveDebouncer, Debouncer, KeyEventHandler, KeyboardHW, Timer};

const NUM_KEYS: usize = 32;

pub fn process<H, T, E>(hw: &mut H, timer: &T, handler: &mut E)
where
    H: KeyboardHW,
    T: Timer,
    E: KeyEventHandler,
{
    let mut debouncer = ActiveDebouncer::default();
    loop {
        let raw = hw.read_keys();
        let (_state, pressed, released) = debouncer.update(raw, timer.millis());
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
