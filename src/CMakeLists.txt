# Collect all source files in the src directory
file(GLOB SRC_FILES "*.c")

# Add sources to the main executable
target_sources(${PROJECT_NAME}.elf PRIVATE ${SRC_FILES})
