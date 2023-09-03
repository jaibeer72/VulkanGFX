cmake_policy(SET CMP0091 NEW)

# Set Minimum requirements for the project 
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set the project name
project(Cross-Platform-VulkanGFX VERSION 0.1.0 LANGUAGES CXX)

# Set the include directories via conan dependencies
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include(${CMAKE_BINARY_DIR}/cmakedeps_macros.cmake)

# Recursively find all source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/Source/*.cpp ${CMAKE_SOURCE_DIR}/Source/*.h ${CMAKE_SOURCE_DIR}/Source/*.hpp)

# Use the natural file system in Xcode
source_group(TREE "${CMAKE_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCE_FILES})

# Include dependencies from Conan
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)


set(CMAKE_SKIP_RPATH TRUE)

# Add executable
add_executable(Cross-Platform-VulkanGFX ${SOURCE_FILES})

# Set C++ standard
# set_property(TARGET Cross-Platform-VulkanGFX PROPERTY CXX_STANDARD 11)

# set Cross-Platform-VulkanGFX as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Cross-Platform-VulkanGFX)

# Link Conan libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan glm::glm glfw)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Source)

