#!/usr/bin/env bash

set -e

echo "Installing dependencies for LLMK..."

if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    echo "Detected Windows..."

    # Check for Chocolatey
    if ! choco -v >/dev/null 2>&1; then
        echo "Chocolatey not found. Installing Chocolatey..."
        powershell -NoProfile -ExecutionPolicy Bypass -Command \
          "Set-ExecutionPolicy Bypass -Scope Process -Force; \
           [System.Net.ServicePointManager]::SecurityProtocol = \
           [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; \
           iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

        echo "Chocolatey installation complete. You may need to restart the terminal."
    fi

    choco install -y gcc-arm-embedded cmake ninja

else
    echo "Detected Unix-based system..."

    # macOS
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "Detected macOS..."
        if ! command -v brew &>/dev/null; then
            echo "Homebrew not found. Installing Homebrew..."
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        fi
        brew install arm-none-eabi-gcc cmake ninja
    fi

    # Linux
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "Detected Linux..."
        sudo apt update

        sudo apt install -y gcc-arm-none-eabi cmake ninja-build
    fi
fi

echo "Dependencies installed successfully."
