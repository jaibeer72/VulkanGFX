#Set Minimum requriements for the project 
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(Cross-Platform-VulkanGFX)

# Get all the source files
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h" "Source/*.hpp")

# Add executable
add_executable(HelloWorld ${SOURCES})

# Set C++ standard
set_property(TARGET HelloWorld PROPERTY CXX_STANDARD 11)