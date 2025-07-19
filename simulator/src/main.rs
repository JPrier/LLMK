mod sim_hal;
mod input_scenario;

use keyboard_core::{KeyEventHandler, KeyboardLogic, KeyboardHW};
use sim_hal::{SimKeyboard, SimTimer};
use input_scenario::example_scenario;

struct PrintHandler;

impl KeyEventHandler for PrintHandler {
    fn key_event(&mut self, key: usize, pressed: bool) {
        println!("key {} {}", key, if pressed { "down" } else { "up" });
    }
}

fn main() {
    let events = example_scenario();
    let mut hw = SimKeyboard::new(4, 8);
    let mut timer = SimTimer::new();
    hw.init();
    let mut logic = KeyboardLogic::new();
    let mut handler = PrintHandler;

    let mut idx = 0;
    while idx < events.len() {
        let ev = &events[idx];
        while timer.millis < ev.time_ms {
            logic.poll(&mut hw, &timer, &mut handler);
            timer.advance(1);
        }
        hw.set_key(ev.row, ev.col, ev.pressed);
        idx += 1;
    }

    // run remaining scans to flush events
    for _ in 0..10 {
        logic.poll(&mut hw, &timer, &mut handler);
        timer.advance(1);
    }
}
