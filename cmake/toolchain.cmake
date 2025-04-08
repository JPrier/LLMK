set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Find ARM GCC toolchain
find_program(ARM_GCC arm-none-eabi-gcc)
find_program(ARM_GXX arm-none-eabi-g++)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy)
find_program(ARM_SIZE arm-none-eabi-size)

# Install ARM toolchain if not found (CI environment)
if(NOT ARM_GCC)
    message(STATUS "ARM GCC not found, attempting to install...")
    execute_process(
        COMMAND sudo apt-get update
        COMMAND sudo apt-get install -y gcc-arm-none-eabi
        RESULT_VARIABLE INSTALL_RESULT
    )
    if(NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install ARM toolchain. Please install manually.")
    endif()
    
    # Try to find the toolchain again
    find_program(ARM_GCC arm-none-eabi-gcc)
    if(NOT ARM_GCC)
        message(FATAL_ERROR "ARM GCC not found even after installation attempt.")
    endif()
endif()

# Set the compilers
set(CMAKE_C_COMPILER ${ARM_GCC})
set(CMAKE_CXX_COMPILER ${ARM_GXX})
set(CMAKE_ASM_COMPILER ${ARM_GCC})
set(CMAKE_OBJCOPY ${ARM_OBJCOPY})
set(CMAKE_SIZE ${ARM_SIZE})

# Set common compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -O2 -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -Wl,--gc-sections -nostartfiles --specs=nano.specs --specs=nosys.specs -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

# Prevent CMake from testing the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
