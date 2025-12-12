cmake_minimum_required(VERSION 3.25)
project(Cross-Platform-VulkanGFX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages (Headers/Loader from vcpkg)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h" "Source/*.hpp")

add_executable(VulkanGFX ${SOURCES})

# Link libraries
target_link_libraries(VulkanGFX PRIVATE glm::glm glfw Vulkan::Vulkan)
target_include_directories(VulkanGFX PUBLIC include src/include lib/include)

# Mac Bundle setting (helps with Window focus)
if (APPLE)
    set_target_properties(VulkanGFX PROPERTIES MACOSX_BUNDLE ON)
endif()