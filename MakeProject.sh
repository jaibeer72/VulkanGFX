#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build
cd build

# check if pip is installed
# if ! command -v pip &> /dev/null
# then
#     echo "pip is not installed. Installing..."
#     sudo apt install python3-pip
# fi

# Check if conan is installed
# if ! command -v conan &> /dev/null
# then
#     echo "Conan is not installed. Installing..."
#     pip install conan
# fi

# run conan install

# Generate the Xcode project
cmake -G "Xcode" ..

echo "Xcode project generated in the build directory."
