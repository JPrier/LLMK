#![no_std]
#![no_main]
use cortex_m::peripheral::{Peripherals, SYST};
use cortex_m_rt::entry;
use keyboard_core::{self as core, KeyboardHW, Timer};
use panic_halt as _;
use stm32h7::stm32h723;

const SYSCLK_HZ: u32 = 64_000_000; // placeholder clock

struct Stm32Keyboard {
    gpio: stm32h723::GPIOC,
}

impl Stm32Keyboard {
    fn new(dp: stm32h723::Peripherals) -> Self {
        Stm32Keyboard { gpio: dp.GPIOC }
    }
}

struct SysTimer {
    syst: SYST,
    start: u64,
}

impl Timer for SysTimer {
    fn millis(&self) -> u64 {
        // Placeholder implementation; a real firmware would track elapsed
        // milliseconds using an interrupt or the DWT cycle counter.
        let _ = self.syst.cvr.read();
        0
    }
}

impl KeyboardHW for Stm32Keyboard {
    fn init(&mut self) {
        // enable port C clock
        let rcc = unsafe { &(*stm32h723::RCC::ptr()) };
        rcc.ahb4enr().modify(|_, w| w.gpiocen().set_bit());

        // configure PC13 as input with pull-up as an example
        self.gpio.moder().modify(|_, w| w.moder13().input());
        self.gpio.pupdr().modify(|_, w| w.pupdr13().pull_up());
    }

    fn read_keys(&self) -> u32 {
        let idr = self.gpio.idr().read().bits();
        (!idr >> 13) & 1
    }
}

#[entry]
fn main() -> ! {
    let dp = stm32h723::Peripherals::take().unwrap();
    let cp = Peripherals::take().unwrap();

    let mut hw = Stm32Keyboard::new(dp);
    let mut syst = cp.SYST;
    syst.set_reload(SYSCLK_HZ / 1000);
    syst.clear_current();
    syst.enable_counter();
    let timer = SysTimer { syst, start: 0 };

    core::run(&mut hw, &timer);
    loop {}
}
