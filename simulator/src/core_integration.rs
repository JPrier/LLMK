use crate::{SimKeyboard, SimTimer, SimEventHandler};
use keyboard_core::{KeyboardHW, Timer, KeyEventHandler, Debouncer};
use std::time::Instant;

// Custom debounce processing that can exit for simulation
pub fn run_simulation_with_debounce<D>(
    hw: &mut SimKeyboard,
    timer: &mut SimTimer,
    handler: &mut SimEventHandler,
    debouncer: &mut D,
    max_time_ms: u64,
) where
    D: Debouncer,
{
    const NUM_ROWS: usize = 4;
    const NUM_COLS: usize = 8; 
    const NUM_KEYS: usize = NUM_ROWS * NUM_COLS;
    
    let mut current_time = 0u64;
    
    while current_time <= max_time_ms {
        // Matrix scanning
        let mut raw_state = 0u64;
        for row in 0..NUM_ROWS {
            hw.set_row_active(row);
            let val = hw.read_keys();
            for col in 0..NUM_COLS {
                if (val >> col) & 1 != 0 {
                    let idx = row * NUM_COLS + col;
                    raw_state |= 1u64 << idx;
                }
            }
        }
        hw.set_all_rows_inactive();

        // Debounce processing
        let (_, pressed, released) = debouncer.update(raw_state, timer.millis());
        
        // Generate key events
        for i in 0..NUM_KEYS {
            let mask = 1u64 << i;
            if pressed & mask != 0 {
                handler.key_event(i, true);
            }
            if released & mask != 0 {
                handler.key_event(i, false);
            }
        }
        
        // Advance time
        timer.advance(1);
        current_time += 1;
    }
}

pub fn benchmark_processing_step<D>(
    hw: &mut SimKeyboard,
    timer: &SimTimer,
    debouncer: &mut D,
) -> (u64, u64) // (raw_state, processing_time_ns)
where
    D: Debouncer,
{
    let start = Instant::now();
    
    const NUM_ROWS: usize = 4;
    const NUM_COLS: usize = 8; 
    
    // Matrix scanning
    let mut raw_state = 0u64;
    for row in 0..NUM_ROWS {
        hw.set_row_active(row);
        let val = hw.read_keys();
        for col in 0..NUM_COLS {
            if (val >> col) & 1 != 0 {
                let idx = row * NUM_COLS + col;
                raw_state |= 1u64 << idx;
            }
        }
    }
    hw.set_all_rows_inactive();

    // Debounce processing
    let _ = debouncer.update(raw_state, timer.millis());
    
    let processing_time = start.elapsed().as_nanos() as u64;
    (raw_state, processing_time)
}