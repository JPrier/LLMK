use keyboard_core::{self as core, KeyboardHW};

struct SimKeyboard;

impl KeyboardHW for SimKeyboard {
    fn init(&mut self) {}
    fn read_keys(&self) -> u32 { 0 }
}

fn main() {
    let mut hw = SimKeyboard;
    core::run(&mut hw);
}
