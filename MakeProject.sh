#!/bin/bash

# Create the build directory if it doesn't exist
# mkdir -p build
# cd build

# check if pip is installed
if ! command -v pip &> /dev/null
then
    echo "pip is not installed. Installing..."
    sudo apt install python3-pip
fi

# Check if conan is installed
if ! command -v conan &> /dev/null
then
    echo "Conan is not installed. Installing..."
    pip install conan
fi

# run conan install
# working commands to make the 
conan install . -s build_type=Debug -c tools.cmake.cmaketoolchain:generator=Xcode --output-folder=ProjectFolder --build missing

# move  to build directory
cd ProjectFolder

# or cmake -B ../ProjectFiles -DCMAKE_TOOLCHAIN_FILE=./build/conan_toolchain.cmake -G Xcode ..

# Generate the Xcode project
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -G Xcode 
#cmake -G "Xcode" ..

echo "Xcode project generated in the build directory."
