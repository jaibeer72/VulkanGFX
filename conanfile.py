from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class YourProjectConan(ConanFile):
    name = "Cross-Platform-VulkanGFX"
    version = "0.0.1b"
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "vulkan-loader/1.3.204.1",     # Replace with the version you need.
        "glm/cci.20230113"  ,   # Replace with the version you need.
        "glfw/3.3.8"
    ]
    generators = "CMakeDeps", "CMakeToolchain"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        
    def package_info(self):
        self.cpp_info.includedirs = ["include", "other_include"]
