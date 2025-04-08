# Collect all source files in the src directory
file(GLOB SRC_FILES "*.c")

# Add sources to the main executable
target_sources(${PROJECT_NAME}.elf PRIVATE ${SRC_FILES})

# Add include directories for src files
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_SOURCE_DIR}/drivers/STM32CubeH7/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
)
