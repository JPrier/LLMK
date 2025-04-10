cmake_minimum_required(VERSION 3.20)

# Project name
project(LLMK C ASM)

# Processor and board configurations
set(MCU_FAMILY STM32H7xx)
set(MCU_MODEL STM32H723xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
)

# Compiler and linker flags
add_compile_options(
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -ffunction-sections
    -fdata-sections
    -fomit-frame-pointer
    -Os
)

add_link_options(
    ${CPU_PARAMETERS}
    -Wl,--gc-sections
    -nostartfiles
    --specs=nano.specs
    --specs=nosys.specs
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/USB/Device
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
)

# Define the target processor
add_definitions(
    -D${MCU_MODEL}
    -DUSE_HAL_DRIVER
    -DCI_BUILD
)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.c"
)

# Executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Generate hex and binary files
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating hex and binary files"
)

# Calculate binary size
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
    COMMENT "Calculating binary size"
)

# Add targets for running linters
add_custom_target(cppcheck
    COMMAND cppcheck --enable=all --std=c99 --platform=arm32-wchar_t4 --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/tools/cppcheck-suppressions.txt -I${CMAKE_CURRENT_SOURCE_DIR}/inc --output-file=${CMAKE_CURRENT_BINARY_DIR}/cppcheck-result.xml ${CMAKE_CURRENT_SOURCE_DIR}/src
    COMMENT "Running Cppcheck static code analysis"
)

# Add targets for running unit tests
add_custom_target(tests
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/tests && make test
    COMMENT "Running Unity unit tests"
)
