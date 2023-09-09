#!/bin/bash

# Default build type
BUILD_TYPE=Debug
IDE_TYPE=Xcode  # Default IDE

# Check for command-line arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -b|--build) BUILD_TYPE="$2"; shift ;;
        -i|--ide) IDE_TYPE="$2"; shift ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done

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
conan install . --output-folder=ProjectFolder --build missing -s build_type=$BUILD_TYPE

if [ $? -ne 0 ]; then
    echo "Conan install failed!"
    #exit 1
fi

# Move to build directory
cd ProjectFolder

# Source the Conan environment script
source conanrun.sh

# Generate the project with the Conan toolchain
if [ "$IDE_TYPE" == "Xcode" ]; then
    cmake -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    echo "Xcode project generated in the ProjectFolder directory."
elif [ "$IDE_TYPE" == "CLion" ]; then
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    echo "CLion project generated in the ProjectFolder directory."
else
    echo "Unsupported IDE type: $IDE_TYPE"
    exit 1
fi


if [ $? -ne 0 ]; then
    echo "CMake project generation failed!"
    #exit 1
fi
