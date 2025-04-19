#!/usr/bin/env bash
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

# Use toolchain if provided via argument
if [[ "$1" == "--stm32" ]]; then
    echo "Configuring project for embedded target..."
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="$PROJECT_ROOT/arm-gcc-toolchain.cmake" -B build/stm32 "$PROJECT_ROOT"
else
    echo "Configuring project for native build..."
    cmake -G Ninja -DHOST_BUILD=ON -B build/host "$PROJECT_ROOT"
fi

# Build the project
echo "Building project..."
cmake --build .

echo "✅ Build succeeded."

