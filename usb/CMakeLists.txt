# Create a dummy source file if no sources exist
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "// Auto-generated dummy file\n")

# Create a static library for USB
add_library(usb STATIC ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)

# Include directories for USB
target_include_directories(usb PUBLIC 
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/${MCU_FAMILY}_HAL_Driver/Inc
)
