#![no_std]

/// Type representing the pressed state of up to 32 keys.
/// Each bit corresponds to a key.
pub type KeyState = u32;

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

#[cfg(feature = "direct-keys")]
mod direct;
#[cfg(feature = "matrix-scan")]
mod matrix;

/// Run the active keyboard algorithm.  This function never returns on the
/// firmware but in the simulator it may exit once the test scenario completes.
pub fn run<H: KeyboardHW, T: Timer>(hw: &mut H, timer: &T) {
    hw.init();

    #[cfg(feature = "matrix-scan")]
    matrix::process(hw, timer);

    #[cfg(feature = "direct-keys")]
    direct::process(hw, timer);
}
