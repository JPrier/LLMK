cmake_minimum_required(VERSION 3.20)
project(LLMK C ASM)

# Set the size utility (adjust the path if necessary)
set(CMAKE_SIZE "arm-none-eabi-size")

# Specify the entry point for the linker (assuming your startup file defines Reset_Handler)
add_link_options(-e Reset_Handler)

#---------------------------------------------------------------------
# Board and CPU Configuration
#---------------------------------------------------------------------
set(MCU_FAMILY STM32H7xx)
set(MCU_MODEL STM32H723xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
)

#---------------------------------------------------------------------
# Compiler Options
#---------------------------------------------------------------------
add_compile_options(
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -ffunction-sections
    -fdata-sections
    -fomit-frame-pointer
    -Os
)

#---------------------------------------------------------------------
# Linker Options
#---------------------------------------------------------------------
add_link_options(
    ${CPU_PARAMETERS}
    -Wl,--gc-sections
    -nostartfiles
    --specs=nano.specs
    --specs=nosys.specs
)

#---------------------------------------------------------------------
# Include Directories
#---------------------------------------------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
)

#---------------------------------------------------------------------
# Preprocessor Definitions
#---------------------------------------------------------------------
add_definitions(
    -D${MCU_MODEL}
    -DUSE_HAL_DRIVER
    -DCI_BUILD
)

#---------------------------------------------------------------------
# Source Files
#---------------------------------------------------------------------
file(GLOB_RECURSE SOURCES "src/*.c")

#---------------------------------------------------------------------
# Executable Target
#---------------------------------------------------------------------
add_executable(${PROJECT_NAME}.elf ${SOURCES})

#---------------------------------------------------------------------
# Post-Build Commands
#  - Generate HEX and BIN files
#  - Calculate binary size
#---------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating HEX and BIN files..."
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
    COMMENT "Calculating binary size..."
)

#---------------------------------------------------------------------
# Custom Targets
#---------------------------------------------------------------------
# Static analysis using Cppcheck
add_custom_target(cppcheck
    COMMAND cppcheck --enable=all --std=c99
            --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/tools/cppcheck-suppressions.txt
            -I${CMAKE_CURRENT_SOURCE_DIR}/inc
            --output-file=${CMAKE_CURRENT_BINARY_DIR}/cppcheck-result.xml
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    COMMENT "Running Cppcheck static analysis..."
)

# Unit tests using Unity (assumes a Makefile exists in tests folder)
add_custom_target(tests
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/tests make test
    COMMENT "Running Unity unit tests..."
)
