cmake_minimum_required(VERSION 3.20)
project(LLMK C ASM)

# ---------------------------------------------------------------------
# Platform Detection
# ---------------------------------------------------------------------
if (CMAKE_TOOLCHAIN_FILE)
    set(TARGET_PLATFORM embedded)
    message(STATUS "Toolchain file detected: ${CMAKE_TOOLCHAIN_FILE}")
    message(STATUS "Configuring for embedded build")
else()
    set(TARGET_PLATFORM native)
    message(STATUS "No toolchain file detected — configuring for native build")
endif()

if(HOST_BUILD)
  add_definitions(-DHOST_BUILD)
  add_library(gpio_accessor tst/dependency/gpio_accessor_mock.c)
else()
  add_library(gpio_accessor src/dependency/gpio_accessor_stm32.c)
endif()

# ---------------------------------------------------------------------
# Embedded Build Configuration (STM32)
# ---------------------------------------------------------------------
if(TARGET_PLATFORM STREQUAL "embedded")
    set(MCU_FAMILY STM32H7xx)
    set(MCU_MODEL STM32H723xx)

    set(CPU_PARAMETERS
        -mcpu=cortex-m7
        -mthumb
        -mfpu=fpv5-d16
        -mfloat-abi=hard
    )

    add_compile_options(
        ${CPU_PARAMETERS}
        -Wall -Wextra
        -ffunction-sections -fdata-sections -fomit-frame-pointer
        -Os
    )

    add_link_options(
        ${CPU_PARAMETERS}
        -Wl,--gc-sections
        -nostartfiles
        -e Reset_Handler
    )

    add_definitions(
        -D${MCU_MODEL}
        -DUSE_HAL_DRIVER
    )

    # Default size utility (customizable if needed)
    set(CMAKE_SIZE "arm-none-eabi-size")
endif()

# ---------------------------------------------------------------------
# Native Build Configuration (local development)
# ---------------------------------------------------------------------
if(TARGET_PLATFORM STREQUAL "native")
    add_compile_options(
        -Wall -Wextra -O2 -g
    )

    add_definitions(
        -DNATIVE_BUILD
    )
endif()

# ---------------------------------------------------------------------
# Include Directories
# ---------------------------------------------------------------------
file(GLOB_RECURSE PROJECT_INCLUDES "${CMAKE_SOURCE_DIR}/inc/*")
include_directories(${PROJECT_INCLUDES})

# ---------------------------------------------------------------------
# Global Preprocessor Defines
# ---------------------------------------------------------------------
add_definitions(
    -DCI_BUILD
)

# ---------------------------------------------------------------------
# Source Files
# ---------------------------------------------------------------------
file(GLOB_RECURSE SOURCES "src/*.c")

# ---------------------------------------------------------------------
# Executable Target
# ---------------------------------------------------------------------
# Host build (macOS)
add_executable(host_tests
  tst/service/test_main.c
)

# STM32 build
add_executable(LLMK.elf
  src/service/main.c
  src/system/system_init.c
  src/logic/matrix_scanner.c
)

# ---------------------------------------------------------------------
# Native-only Development Tools (Tests, SCA, Benchmarks)
# ---------------------------------------------------------------------
if(TARGET_PLATFORM STREQUAL "native")
    # Static analysis with cppcheck
    add_custom_target(cppcheck
        COMMAND cppcheck --enable=all --std=c99
            --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/tools/cppcheck-suppressions.txt
            -I${CMAKE_CURRENT_SOURCE_DIR}/inc
            --output-file=${CMAKE_CURRENT_BINARY_DIR}/cppcheck-result.xml
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMENT "Running Cppcheck static analysis..."
    )

    # Unity-based unit tests (assumes Makefile in tests/)
    add_custom_target(tests
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/tests make test
        COMMENT "Running Unity unit tests..."
    )
endif()

