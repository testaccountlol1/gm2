#!/bin/bash
set -euo pipefail
OS="$(uname -s)"
echo "Checking dependencies on $OS..."
#the reason theres no windows and the correctly working thing only works for arch is cuz i only like arhc and fuck every other os
install_dependencies() {
    if [ "$OS" = "Linux" ]; then
        if [ -f /etc/debian_version ]; then
            sudo apt update && sudo apt install -y build-essential
        elif [ -f /etc/redhat-release ]; then
            sudo dnf groupinstall -y "Development Tools"
        elif [ -f /etc/arch-release ]; then
            sudo pacman -S --noconfirm --needed base-devel valkey sfml hiredis
            git clone https://archlinux.org/aur/yay.git
            cd yay
            makepkg -si --noconfirm
            cd ..
            yay -S --noconfirm redis-plus-plus
        else
            echo "Unknown Linux distro. Please install make and g++ manually."
            exit 1
        fi
    elif [ "$OS" = "Darwin" ]; then
        echo "macOS detected. Installing Xcode Command Line Tools..."
        xcode-select --install
    else
        echo "Unsupported OS."
        exit 1
    fi
}

# Install tools if either g++ or make is missing
if ! command -v g++ &> /dev/null || ! command -v make &> /dev/null; then
    install_dependencies
fi

echo "Dependencies ready. Executing make run..."
valkey-server &
cd code && make run
