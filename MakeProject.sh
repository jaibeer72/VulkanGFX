#!/bin/bash

# Default build type
BUILD_TYPE=Debug

# Check for command-line argument for build type
if [ "$1" ]; then
    BUILD_TYPE=$1
fi

# Check if pip is installed
if ! command -v pip &> /dev/null; then
    echo "pip is not installed. Installing..."
    sudo apt install python3-pip
fi

# Check if conan is installed
if ! command -v conan &> /dev/null; then
    echo "Conan is not installed. Installing..."
    pip install conan
fi

# Detect Conan profile
conan profile detect

# Run Conan install with the specified build type
conan install . -c tools.cmake.cmaketoolchain:generator=xcode --output-folder=ProjectFolder --build missing -s build_type=$BUILD_TYPE

if [ $? -ne 0 ]; then
    echo "Conan install failed!"
    exit 1
fi

# Move to build directory
cd ProjectFolder

# Source the Conan environment script
source conanrun.sh

# Generate the Xcode project with the Conan toolchain
cmake -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ..

if [ $? -ne 0 ]; then
    echo "CMake project generation failed!"
    exit 1
fi


echo "Xcode project generated in the ProjectFolder directory."
