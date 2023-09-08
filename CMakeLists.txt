cmake_minimum_required(VERSION 3.22.6)

project(Cross-Platform-VulkanGFX VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
if(APPLE)
    find_package(MoltenVK REQUIRED)
else()
    find_package(Vulkan REQUIRED)
endif()

file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h" "Source/*.hpp")

source_group(TREE "${CMAKE_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCES})

add_executable(VulkanGFX ${SOURCES})

if(APPLE)
    target_link_libraries(VulkanGFX PRIVATE glm::glm glfw moltenvk::moltenvk)
else()
    target_link_libraries(VulkanGFX PRIVATE glm::glm glfw Vulkan::Vulkan)
endif()

target_include_directories(VulkanGFX PRIVATE include src/include lib/include)