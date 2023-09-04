from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class VulkanGFXConan(ConanFile):
    name = "Cross-Platform-VulkanGFX"
    version = "0.0.1b"
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "vulkan-loader/1.3.239.0",
        "glm/cci.20230113",
        "glfw/3.3.8"
    ]
    generators = "CMakeDeps", "CMakeToolchain" 

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package_info(self):
        self.cpp_info.includedirs = ["include", "src/include", "lib/include"]

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")
