#!/usr/bin/env bash
set -e

trap 'echo -e "\n[💥 Script ended] Press enter to close..."; read' EXIT

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

# Set the build output path based on target
if [[ "$1" == "--stm32" ]]; then
    BUILD_DIR="$PROJECT_ROOT/build/stm32"
else
    BUILD_DIR="$PROJECT_ROOT/build/host"
fi

# Use toolchain if provided via argument
if [[ "$1" == "--stm32" ]]; then
    echo "Configuring project for embedded target..."
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="$PROJECT_ROOT/arm-gcc-toolchain.cmake" -B "$BUILD_DIR" "$PROJECT_ROOT"
else
    echo "Configuring project for native build..."
    cmake -G Ninja -DHOST_BUILD=ON -B "$BUILD_DIR" "$PROJECT_ROOT"
fi

# Build the project
echo "Building project..."
cmake --build "$BUILD_DIR" -- -j4

echo "✅ Build succeeded."

