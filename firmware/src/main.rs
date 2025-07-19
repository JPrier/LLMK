#![no_std]
#![no_main]
use cortex_m_rt::entry;
use panic_halt as _;
use keyboard_core::{self as core, KeyboardHW};

struct Stm32Keyboard;

impl KeyboardHW for Stm32Keyboard {
    fn init(&mut self) {}
    fn read_keys(&self) -> u32 { 0 }
}

#[entry]
fn main() -> ! {
    let mut hw = Stm32Keyboard;
    core::run(&mut hw);
    loop {}
}
