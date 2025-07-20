// Debouncer implementations and trait

use crate::KeyState;

pub trait Debouncer {
    /// Update debouncer with raw key state and current time in milliseconds.
    /// Returns: (debounced state, newly pressed mask, newly released mask)
    fn update(&mut self, raw: KeyState, time_ms: u64) -> (KeyState, KeyState, KeyState);
}

/// No debouncing - pass raw state through.
pub struct NoDebounce {
    prev_state: KeyState,
}

impl NoDebounce {
    pub fn new() -> Self {
        Self { prev_state: 0 }
    }
}

impl Default for NoDebounce {
    fn default() -> Self {
        Self::new()
    }
}

impl Debouncer for NoDebounce {
    fn update(&mut self, raw: KeyState, _t: u64) -> (KeyState, KeyState, KeyState) {
        let changed = raw ^ self.prev_state;
        let pressed = changed & raw;
        let released = changed & !raw;
        self.prev_state = raw;
        (raw, pressed, released)
    }
}

/// Time based debouncer. Each key must be stable for `debounce_ms` before state changes.
pub struct TimeDebounce {
    last_change: [u64; 64],
    stable_state: KeyState,
    debounce_ms: u64,
}

impl TimeDebounce {
    pub fn new(debounce_ms: u64) -> Self {
        Self {
            last_change: [0; 64],
            stable_state: 0,
            debounce_ms,
        }
    }
}

impl Default for TimeDebounce {
    fn default() -> Self {
        Self::new(5)
    }
}

impl Debouncer for TimeDebounce {
    fn update(&mut self, raw: KeyState, now: u64) -> (KeyState, KeyState, KeyState) {
        let mut pressed = 0;
        let mut released = 0;
        for i in 0..64 {
            let mask = 1u64 << i;
            let is_now = raw & mask != 0;
            let was = self.stable_state & mask != 0;
            if is_now != was {
                if now - self.last_change[i] >= self.debounce_ms {
                    if is_now {
                        pressed |= mask;
                    } else {
                        released |= mask;
                    }
                    self.stable_state ^= mask;
                    self.last_change[i] = now;
                }
            } else {
                self.last_change[i] = now;
            }
        }
        (self.stable_state, pressed, released)
    }
}

/// Bit mask history debouncer. A key must be seen in the same state for `threshold` consecutive scans.
pub struct MaskDebounce {
    history: [u8; 64],
    state: KeyState,
    threshold: u8,
}

impl MaskDebounce {
    pub fn new(threshold: u8) -> Self {
        Self {
            history: [0; 64],
            state: 0,
            threshold,
        }
    }
}

impl Default for MaskDebounce {
    fn default() -> Self {
        Self::new(5)
    }
}

impl Debouncer for MaskDebounce {
    fn update(&mut self, raw: KeyState, _now: u64) -> (KeyState, KeyState, KeyState) {
        let mut pressed = 0;
        let mut released = 0;
        for i in 0..64 {
            let mask = 1u64 << i;
            let bit = if raw & mask != 0 { 1 } else { 0 };
            self.history[i] = (self.history[i] << 1) | bit;
            let ones = self.history[i].count_ones() as u8;
            let cur = self.state & mask != 0;
            if ones == self.threshold {
                if bit == 1 && !cur {
                    self.state |= mask;
                    pressed |= mask;
                } else if bit == 0 && cur {
                    self.state &= !mask;
                    released |= mask;
                }
            }
        }
        (self.state, pressed, released)
    }
}

#[cfg(feature = "no-debounce")]
pub type ActiveDebouncer = NoDebounce;

#[cfg(feature = "time-debounce")]
pub type ActiveDebouncer = TimeDebounce;

#[cfg(feature = "mask-debounce")]
pub type ActiveDebouncer = MaskDebounce;
