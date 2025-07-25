#![no_std]
#![no_main]
use cortex_m::peripheral::{Peripherals, SYST};
use cortex_m_rt::entry;
use keyboard_core::{self as core, KeyEventHandler, KeyboardHW, Timer};
use panic_halt as _;
use stm32h7::stm32h723;

const SYSCLK_HZ: u32 = 64_000_000; // placeholder clock

struct Stm32Keyboard {
    gpio: stm32h723::GPIOC,
}

const _ROW_PINS: [usize; 4] = [0, 1, 2, 3];
const _COL_PINS: [usize; 8] = [4, 5, 6, 7, 8, 9, 10, 11];

impl Stm32Keyboard {
    fn new(dp: stm32h723::Peripherals) -> Self {
        Stm32Keyboard { gpio: dp.GPIOC }
    }
}

struct SysTimer {
    syst: SYST,
    start: u64,
}

struct EventSink;

impl KeyEventHandler for EventSink {
    fn key_event(&mut self, _key: usize, _pressed: bool) {
        // in real firmware this would update USB HID reports
    }
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

        // rows as outputs
        self.gpio.moder().modify(|_, w| {
            w.moder0().output();
            w.moder1().output();
            w.moder2().output();
            w.moder3().output()
        });
        // columns as inputs with pull-ups
        self.gpio.moder().modify(|_, w| {
            w.moder4().input();
            w.moder5().input();
            w.moder6().input();
            w.moder7().input();
            w.moder8().input();
            w.moder9().input();
            w.moder10().input();
            w.moder11().input()
        });
        self.gpio.pupdr().modify(|_, w| {
            w.pupdr4().pull_up();
            w.pupdr5().pull_up();
            w.pupdr6().pull_up();
            w.pupdr7().pull_up();
            w.pupdr8().pull_up();
            w.pupdr9().pull_up();
            w.pupdr10().pull_up();
            w.pupdr11().pull_up();
            w.pupdr0().floating();
            w.pupdr1().floating();
            w.pupdr2().floating();
            w.pupdr3().floating()
        });

        self.set_all_rows_inactive();
    }

    fn read_keys(&self) -> u64 {
        let idr = self.gpio.idr().read().bits();
        ((!idr >> 4) & 0xff) as u64
    }

    fn set_row_active(&mut self, row: usize) {
        self.set_all_rows_inactive();
        match row {
            0 => { self.gpio.bsrr().write(|w| w.br0().reset()); }
            1 => { self.gpio.bsrr().write(|w| w.br1().reset()); }
            2 => { self.gpio.bsrr().write(|w| w.br2().reset()); }
            3 => { self.gpio.bsrr().write(|w| w.br3().reset()); }
            _ => {}
        }
    }

    fn set_all_rows_inactive(&mut self) {
        self.gpio
            .bsrr()
            .write(|w| w.bs0().set_().bs1().set_().bs2().set_().bs3().set_());
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
    let mut events = EventSink;

    core::run(&mut hw, &timer, &mut events);
    loop {}
}
