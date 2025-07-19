use keyboard_core::{self as core, KeyboardHW, Timer};
use std::time::Instant;

struct SimKeyboard;

impl KeyboardHW for SimKeyboard {
    fn init(&mut self) {}
    fn read_keys(&self) -> u32 {
        0
    }
}

struct HostTimer(Instant);

impl HostTimer {
    fn new() -> Self {
        HostTimer(Instant::now())
    }
}

impl Timer for HostTimer {
    fn millis(&self) -> u64 {
        self.0.elapsed().as_millis() as u64
    }
}

fn main() {
    let mut hw = SimKeyboard;
    let timer = HostTimer::new();
    core::run(&mut hw, &timer);
}
