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
  - `/service` - Main application logic and entry point
  - `/system` - System initialization and hardware configuration
  - `/dependency` - Hardware abstraction implementations
  - `/logic` - Core keyboard logic algorithms
- `/inc` - Header files
  - `/dependency` - Interface definitions for hardware abstraction
  - `/system` - STM32 system headers and CMSIS
  - `/logic` - Core algorithm declarations 
  - `/service` - Service layer declarations
  - `/data` - Data structure declarations
- `/drivers` - STM32 HAL drivers and custom low-level drivers
  - `/STM32CubeH7` - STM32CubeH7 drivers (submodule)
- `/startup` - CMSIS startup files and linker scripts
- `/scripts` - Installation and utility scripts
- `/tools` - Development tools and configuration
- `/tst` - Test files and mocks
- `/development` - Development documentation
- `/build` - Compiled output (not tracked in git)

## Submodules
This project uses Git submodules for external dependencies. After cloning the repository, initialize and update the submodules:

```bash
git submodule update --init --recursive
```

The main submodule is:
- `drivers/STM32CubeH7` - STM32CubeH7 HAL and LL drivers from STMicroelectronics

## Development Setup

To set up your development environment for building LLMK, follow the steps below based on your operating system.

### Windows

1. **Install Dependencies:**
   - Navigate to the scripts directory in the repository
   - Open a command prompt with administrator privileges
   - Run the installation script:
     ```cmd
     cd path\to\LLMK\scripts
     install_dependencies.bat
     ```
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
     - Ninja build system
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
   - Navigate to the repository's scripts directory and run the installation script:
     ```bash
     cd /path/to/LLMK/scripts
     chmod +x install_dependencies.sh
     ./install_dependencies.sh
     ```
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
     - Ninja build system
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
   - Navigate to the repository's scripts directory and run the installation script:
     ```bash
     cd /path/to/LLMK/scripts
     chmod +x install_dependencies.sh
     ./install_dependencies.sh
     ```
   - This will install:
     - ARM GCC toolchain
     - CMake (version 3.20+)
     - Ninja build system
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

## Continuous Integration

The project uses GitHub Actions for continuous integration, providing automated building and static analysis on all pushes to the main branch and pull requests.

### CI Pipeline

The CI pipeline consists of two main jobs:

1. **Build:**
   - Checks out the repository and its submodules
   - Installs the ARM GCC toolchain and Ninja build system
   - Configures the project with CMake
   - Builds the firmware
   - Uploads the compiled firmware as artifacts

2. **Static Analysis:**
   - Runs Cppcheck on the codebase
   - Uploads the analysis results as artifacts

### Running Static Analysis Locally

You can run the same static analysis tools locally:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --target cppcheck
```

The analysis results will be written to `build/cppcheck-result.xml`.

## Testing

The project includes a test framework for verifying functionality in a native environment (without requiring actual hardware).

### Running Tests

To run the tests:

```bash
# Configure for native (host) build
mkdir -p build
cd build
cmake .. -DHOST_BUILD=ON

# Build and run tests
cmake --build . --target host_tests
./host_tests
```

The test framework uses mock implementations of hardware-dependent components, allowing the core logic to be tested on a development machine.

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
