# Minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Basic cross-compilation settings
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the cross-compilers
set(CMAKE_C_COMPILER arm-none-eabi-gcc CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++ CACHE FILEPATH "" FORCE)

# Optionally, set the assembler and other tools
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc CACHE FILEPATH "" FORCE)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

# Ensure CMake searches only within the specified root paths
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Workaround for bare-metal toolchain:
# Force CMake's try-compile tests to build as a static library instead of a full executable.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)



