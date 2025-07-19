# LLMK Rust Firmware Workspace

This repository contains a Rust workspace for developing an ultra-low-latency keyboard firmware targeting the STM32H723 microcontroller.  

Workspace crates:

- `core` – hardware agnostic keyboard logic
- `firmware` – STM32H723 implementation
- `simulator` – Linux host simulation
- `bootloader` – minimal bootloader

The project currently contains only skeleton implementations.  See the planning discussion for further details.
