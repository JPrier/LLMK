#![no_std]

/// Hardware-agnostic keyboard logic will live here.

pub trait KeyboardHW {
    fn init(&mut self) {}
    fn read_keys(&self) -> u32 { 0 }
}

pub fn run<H: KeyboardHW>(hw: &mut H) {
    hw.init();
    let _state = hw.read_keys();
    let _ = _state; // placeholder
}
