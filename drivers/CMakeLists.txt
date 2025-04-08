# Create a dummy source file if no sources exist
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "// Auto-generated dummy file\n")

# Create a static library for drivers
add_library(drivers STATIC ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)

# Include directories for drivers
target_include_directories(drivers PUBLIC 
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
)
