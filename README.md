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

To set up your development environment for building LLMK, follow the steps below based on your operating system.

### Windows

1. **Install Dependencies:**
   - Right-click on the `install_dependencies.bat` script and select "Run as administrator" to install the necessary tools.
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
   - You will be prompted if you want to install STM32CubeProgrammer (recommended for flashing)

2. **Build the Firmware:**
   - Open Command Prompt.
   - Navigate to the repository directory:
     ```cmd
     cd path\to\LLMK
     ```
   - Create a build directory and navigate into it:
     ```cmd
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```cmd
     cmake ..
     ```
   - Build the project:
     ```cmd
     cmake --build .
     ```

### macOS

1. **Install Dependencies:**
   - Open Terminal.
   - Navigate to the repository directory and run the installation script:
     ```bash
     cd /path/to/LLMK
     chmod +x install_dependencies.sh
     ./install_dependencies.sh
     ```
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
   - You will be prompted if you want to install OpenOCD (recommended for flashing)

2. **Build the Firmware:**
   - In Terminal, navigate to the repository directory:
     ```bash
     cd /path/to/LLMK
     ```
   - Create a build directory and navigate into it:
     ```bash
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```bash
     cmake ..
     ```
   - Build the project:
     ```bash
     make
     ```

### Linux (Debian/Ubuntu-based)

1. **Install Dependencies:**
   - Open Terminal.
   - Navigate to the repository directory and run the installation script:
     ```bash
     cd /path/to/LLMK
     chmod +x install_dependencies.sh
     ./install_dependencies.sh
     ```
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
   - You will be prompted if you want to install OpenOCD (recommended for flashing)

2. **Build the Firmware:**
   - In Terminal, navigate to the repository directory:
     ```bash
     cd /path/to/LLMK
     ```
   - Create a build directory and navigate into it:
     ```bash
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```bash
     cmake ..
     ```
   - Build the project:
     ```bash
     make
     ```

## Flashing the Firmware

After building the firmware, you can flash it to your STM32 microcontroller using one of the following methods:

### Using STM32CubeProgrammer (Windows/macOS/Linux)
1. Connect your ST-Link programmer to the STM32H723ZGT6 board
2. Open STM32CubeProgrammer
3. Select the correct interface (ST-Link)
4. Click "Connect"
5. Navigate to "Erasing & Programming"
6. Select the firmware binary file (build/LLMK.bin)
7. Set the start address to 0x08000000
8. Click "Start Programming"

### Using OpenOCD (macOS/Linux)
```bash
openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program build/LLMK.bin 0x08000000 verify reset exit"
```

### Using ST-Flash (macOS/Linux)
```bash
st-flash write build/LLMK.bin 0x08000000
```
