cmake_minimum_required(VERSION 3.20)
project(LLMK C ASM)

# ---------------------------------------------------------------------
# Configurations
# ---------------------------------------------------------------------
include(cmake/build_config.cmake)

# Inject into compiler
add_definitions(
  -DNUM_ROWS=${NUM_ROWS}
  -DNUM_COLS=${NUM_COLS}
)

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
        -e Reset_Handler
    )

    add_definitions(
        -D${MCU_MODEL}
        -DUSE_HAL_DRIVER
        -D__ARM_ARCH_PROFILE=\'M\'
    )

    # Default size utility (customizable if needed)
    set(CMAKE_SIZE "arm-none-eabi-size")

    set(LDSCRIPT ${CMAKE_SOURCE_DIR}/startup/STM32H723ZGTX_FLASH.ld)
    add_link_options(-T${LDSCRIPT})
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
include_directories(
  ${CMAKE_SOURCE_DIR}/inc
  ${CMAKE_SOURCE_DIR}/inc/dependency
  ${CMAKE_SOURCE_DIR}/inc/system
  ${CMAKE_SOURCE_DIR}/inc/system/CMSIS
  ${CMAKE_SOURCE_DIR}/inc/logic
  ${CMAKE_SOURCE_DIR}/inc/data
  ${CMAKE_SOURCE_DIR}/inc/service
)


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
if(HOST_BUILD)
  add_executable(host_tests
    tst/service/test_main.c
    tst/dependency/gpio_accessor_mock.c
    src/logic/matrix_scanner.c
    # Do NOT include system_init.c or anything that includes STM32 headers
  )
else()
  add_executable(LLMK.elf
    startup/startup_stm32h723zgtx.s
    src/system/system_stm32h7xx.c
    src/service/main.c
    src/dependency/gpio_accessor_stm32.c
  )
endif()


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

