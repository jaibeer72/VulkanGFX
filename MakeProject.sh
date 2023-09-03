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

conan profile detect

conan install . -s build_type=Debug  --output-folder=ProjectFolder --build missing
if [ $? -ne 0 ]; then
    echo "Conan install failed!"
    # exit 1
fi

# move  to build directory
cd ProjectFolder

source conanbuild.sh

if [ $? -ne 0 ]; then
    echo "Failed to change directory to ProjectFolder!"
    # exit 1
fi

# or cmake -B ../ProjectFiles -DCMAKE_TOOLCHAIN_FILE=./build/conan_toolchain.cmake -G Xcode ..

# Generate the Xcode project
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmakedeps_macros.cmake -G Xcode
if [ $? -ne 0 ]; then
    echo "CMake project generation failed!"
    # exit 1
fi
#cmake -G "Xcode" ..

source deactivate_conanbuild.sh

echo "Xcode project generated in the build directory."
