#![no_std]
#![no_main]
use cortex_m::asm;
use cortex_m_rt::entry;
use panic_halt as _;
use stm32h7::stm32h723;

const APP_BASE: u32 = 0x0800_8000;

#[entry]
fn main() -> ! {
    let dp = stm32h723::Peripherals::take().unwrap();

    // enable port C clock to read a key or button on PC13
    dp.RCC.ahb4enr().modify(|_, w| w.gpiocen().set_bit());
    dp.GPIOC.moder().modify(|_, w| w.moder13().input());
    dp.GPIOC.pupdr().modify(|_, w| w.pupdr13().pull_up());

    let pressed = dp.GPIOC.idr().read().idr13().bit_is_clear();

    if !pressed {
        unsafe { asm::bootload(APP_BASE as *const u32) };
    }

    // Stay in bootloader (update mode)
    loop {}
}
