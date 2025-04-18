#!/usr/bin/env bash

# ====================================================
# Build script for LLMK (run from LLMK/scripts/Unix)
# This script switches to the project root (two directories up),
# removes any existing build folder, creates a new one,
# configures CMake with the Ninja generator and the ARM toolchain,
# and then builds the project.
# ====================================================

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
echo "Project root is: $PROJECT_ROOT"

# Remove existing build folder
if [ -d "$PROJECT_ROOT/build" ]; then
    echo "Removing existing build folder..."
    rm -rf "$PROJECT_ROOT/build"
fi

# Create build directory
echo "Creating build folder..."
mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build"

# Run CMake configuration
echo "Configuring project with CMake..."
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="$PROJECT_ROOT/arm-gcc-toolchain.cmake" "$PROJECT_ROOT"

# Build the project
echo "Building project..."
cmake --build .

echo "✅ Build succeeded."
