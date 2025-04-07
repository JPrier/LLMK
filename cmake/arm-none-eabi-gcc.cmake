set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Set toolchain programs
find_program(ARM_GCC arm-none-eabi-gcc)
find_program(ARM_GPP arm-none-eabi-g++)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy)
find_program(ARM_SIZE arm-none-eabi-size)
find_program(ARM_GDB arm-none-eabi-gdb)

# Set the target-specific executables
set(CMAKE_C_COMPILER ${ARM_GCC})
set(CMAKE_CXX_COMPILER ${ARM_GPP})
set(CMAKE_OBJCOPY ${ARM_OBJCOPY})
set(CMAKE_SIZE ${ARM_SIZE})
set(CMAKE_GDB ${ARM_GDB})

# Don't look for programs on the host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
