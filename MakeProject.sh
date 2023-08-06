#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build
cd build

# Generate the Xcode project
cmake -G "Xcode" ..

echo "Xcode project generated in the build directory."
