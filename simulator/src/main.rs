mod sim_hal;
mod input_scenario;

use sim_hal::{SimKeyboard, SimTimer};
use input_scenario::example_scenario;
use keyboard_core::KeyboardHW;

fn scan_and_process(hw: &mut impl KeyboardHW, time: u64) {
    let keys = hw.read_keys();
    if keys != 0 {
        println!("[{} ms] Keys: {:064b}", time, keys);
    }
}

fn main() {
    let mut hw = SimKeyboard::new(4, 4);
    let mut timer = SimTimer::new();
    let events = example_scenario();

    let max_time = events.iter().map(|e| e.time_ms).max().unwrap_or(0) + 20;

    let mut tick_ms = 0;
    let mut event_idx = 0;

    while tick_ms <= max_time {
        while event_idx < events.len() && events[event_idx].time_ms == tick_ms {
            let ev = &events[event_idx];
            hw.set_key(ev.row, ev.col, ev.pressed);
            println!(
                "[{} ms] Key {}:{} {}",
                tick_ms,
                ev.row,
                ev.col,
                if ev.pressed { "pressed" } else { "released" }
            );
            event_idx += 1;
        }

        hw.set_all_rows_inactive();

        for row in 0..4 {
            hw.set_row_active(row);
            scan_and_process(&mut hw, tick_ms);
        }

        timer.advance(1);
        tick_ms += 1;
    }

    println!("✅ Simulation complete.");
}
