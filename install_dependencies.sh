
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Installing dependencies for LLMK on macOS..."

    if ! command -v brew &>/dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    brew tap ArmMbed/homebrew-formulae

    brew install arm-none-eabi-gcc

    brew install cmake

    read -p "Do you want to install OpenOCD for flashing? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        brew install openocd
    fi

    echo "Dependencies installed successfully."

else
    echo "Installing dependencies for LLMK on Linux..."

    sudo apt update

    sudo apt install -y gcc-arm-none-eabi

    sudo apt install -y cmake

    read -p "Do you want to install OpenOCD for flashing? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        sudo apt install -y openocd
    fi

    echo "Dependencies installed successfully."
fi
