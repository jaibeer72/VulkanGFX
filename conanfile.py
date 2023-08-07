from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.apple import XcodeDeps
from conan.tools.apple import XcodeBuild

class YourProjectConan(ConanFile):
    name = "Cross-Platform-VulkanGFX"
    version = "0.0.1b"
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "glfw/3.3.2",     # Replace with the version you need.
        "glm/cci.20230113"     # Replace with the version you need.
    ]
    generators = "CMakeDeps", "CMakeToolchain"

    def generate(self):
        xcode = XcodeDeps(self)
        xcode.generate()

    def build(self):
        xcodebuild = XcodeBuild(self)
        xcodebuild.build("app.xcodeproj")
