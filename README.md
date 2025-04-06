# LLMK - Low-Latency Mechanical Keyboard

## Overview
Custom tenkeyless mechanical keyboard optimized for ultra-low latency input on Windows gaming PCs, built around the STM32H723ZGT6 microcontroller.

## Features
- STM32H723ZGT6 Core Board (550 MHz, 1MB Flash, 564KB RAM)
- Optical switches for faster response times
- Direct GPIO connections for each key (no matrix scanning)
- Optimized for minimal input latency
- USB Full-Speed communication

## Project Structure
- `/src` - Application logic source files
- `/inc` - Header files
- `/drivers` - STM32 HAL drivers and custom low-level drivers
- `/usb` - USB device stack implementation
- `/startup` - CMSIS startup files and linker scripts
- `/build` - Compiled output (not tracked in git)

## Development Setup
1. Install STM32CubeIDE and/or STM32CubeMX
2. Install CMake (version 3.20+)
3. Install arm-none-eabi-gcc toolchain
4. Install STM32CubeProgrammer for flashing

## Building the Project
```bash
mkdir -p build && cd build
cmake ..
make
```

## Flashing the Firmware
Use STM32CubeProgrammer or OpenOCD with an ST-Link programmer.
