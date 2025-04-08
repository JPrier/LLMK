# Collect all startup files (e.g., assembly or C)
file(GLOB STARTUP_FILES "*.s" "*.c")

# Add startup files to the main executable
target_sources(${PROJECT_NAME}.elf PRIVATE ${STARTUP_FILES})
