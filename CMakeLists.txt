cmake_policy(SET CMP0091 NEW)

# Set the project name
project(Cross-Platform-VulkanGFX)

#Set Minimum requriements for the project 
cmake_minimum_required(VERSION 3.5)

# Recursively find all source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/Source/*.cpp ${CMAKE_SOURCE_DIR}/Source/*.h ${CMAKE_SOURCE_DIR}/Source/*.hpp)

# Create a source group for each directory in the Source folder
foreach(FILE ${SOURCE_FILES})
    # Get the relative path of the file with respect to the Source directory
    file(RELATIVE_PATH RELATIVE_PATH "${CMAKE_SOURCE_DIR}/Source" "${FILE}")

    # Get the directory of the relative path
    get_filename_component(PARENT_DIR "${RELATIVE_PATH}" DIRECTORY)

    # Use windows slashes for Visual Studio
    string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")

    # Group into "Source" group
    source_group("Source\\${GROUP}" FILES "${FILE}")
endforeach()

# Create a source group for each directory in the Docs folder
file(GLOB DOC_FILES ${CMAKE_SOURCE_DIR}/Docs/*.md)
add_custom_target(Docs SOURCES ${DOC_FILES})

# Set the include directories via conan dependencies
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Include dependencies from Conan
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)


# Add executable
add_executable(Cross-Platform-VulkanGFX ${SOURCE_FILES})

# Set C++ standard
set_property(TARGET Cross-Platform-VulkanGFX PROPERTY CXX_STANDARD 11)

# set Cross-Platform-VulkanGFX as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Cross-Platform-VulkanGFX)

# # Link Conan libraries
 target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan glm::glm glfw)
 target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
