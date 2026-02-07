cmake_minimum_required(VERSION 3.25)
project(Cross-Platform-VulkanGFX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages (Headers/Loader from vcpkg)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(vk-bootstrap CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h" "Source/*.hpp")
# Exclude example sources from the main build; examples are separate targets
list(FILTER SOURCES EXCLUDE REGEX ".*/Source/Examples/.*")

add_executable(VulkanGFX ${SOURCES})

# Link libraries
target_link_libraries(VulkanGFX PRIVATE glm::glm glfw Vulkan::Vulkan vk-bootstrap::vk-bootstrap)
target_include_directories(VulkanGFX PUBLIC include src/include lib/include)

# Mac Bundle setting (helps with Window focus)
if (APPLE)
    set_target_properties(VulkanGFX PROPERTIES MACOSX_BUNDLE ON)
endif()

# Optionally build a small vk-bootstrap GLFW example to see integration
option(BUILD_VKB_EXAMPLE "Build vk-bootstrap GLFW example" ON)
if (BUILD_VKB_EXAMPLE)
    add_executable(vk_bootstrap_example Source/Examples/vk_bootstrap_example.cpp)
    target_link_libraries(vk_bootstrap_example PRIVATE glm::glm glfw Vulkan::Vulkan vk-bootstrap::vk-bootstrap)
    if(UNIX)
        target_link_libraries(vk_bootstrap_example PRIVATE ${CMAKE_DL_LIBS})
    endif()
    target_include_directories(vk_bootstrap_example PUBLIC include src/include lib/include)
endif()