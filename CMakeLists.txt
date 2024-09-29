cmake_minimum_required(VERSION 3.22.6)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Cross-Platform-VulkanGFX VERSION 0.0.1)

# Find required packages
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)  # Make sure VulkanLoader is installed and its CMake configuration is found

# List your source files
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h" "Source/*.hpp")

# Create executable
add_executable(VulkanGFX ${SOURCES})

# Link against required libraries
target_link_libraries(VulkanGFX PUBLIC glm::glm glfw Vulkan::Vulkan)

# Include directories
target_include_directories(VulkanGFX PUBLIC include src/include lib/include)