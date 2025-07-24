#![no_std]

#[cfg(test)]
extern crate std;

/// Type representing the pressed state of up to 32 keys.
/// Each bit corresponds to a key.
/// Type representing the pressed state of up to 64 keys.
/// Each bit corresponds to a key.
pub type KeyState = u64;

pub mod debounce;
#[cfg(any(
    feature = "no-debounce",
    feature = "time-debounce",
    feature = "mask-debounce"
))]
pub use debounce::ActiveDebouncer;
pub use debounce::{Debouncer, MaskDebounce, NoDebounce, TimeDebounce};

/// Abstraction over the hardware keyboard interface.  This trait is
/// implemented by the STM32 firmware as well as the Linux simulator.
pub trait KeyboardHW {
    /// Perform any one time initialisation of the hardware.
    fn init(&mut self) {}

    /// Read the current key state.  For a matrix this reads the currently
    /// active row; for direct wiring it reads all keys.
    fn read_keys(&self) -> KeyState {
        0
    }

    /// Activate a row in a matrix keyboard.  Direct keyboards can ignore this.
    fn set_row_active(&mut self, _row: usize) {}

    /// Deactivate all rows.
    fn set_all_rows_inactive(&mut self) {}
}

/// Simple timer abstraction used by the debouncing logic.
pub trait Timer {
    /// Return milliseconds since startup.
    fn millis(&self) -> u64;
}

/// Handler for debounced key events. `pressed` is true for a key down event
/// and false for a release. The `key` index corresponds to the bit position in
/// `KeyState`.
pub trait KeyEventHandler {
    fn key_event(&mut self, key: usize, pressed: bool);
}

#[cfg(feature = "direct-keys")]
mod direct;
#[cfg(feature = "matrix-scan")]
mod matrix;

mod logic;
pub use logic::KeyboardLogic;

/// Run the active keyboard algorithm.  This function never returns on the
/// firmware but in the simulator it may exit once the test scenario completes.
pub fn run<H, T, E>(hw: &mut H, timer: &T, handler: &mut E)
where
    H: KeyboardHW,
    T: Timer,
    E: KeyEventHandler,
{
    hw.init();

    #[cfg(feature = "matrix-scan")]
    matrix::process(hw, timer, handler);

    #[cfg(feature = "direct-keys")]
    direct::process(hw, timer, handler);
}
