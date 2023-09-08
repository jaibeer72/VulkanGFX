from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.apple import fix_apple_shared_install_name

class VulkanGFXConan(ConanFile):
    name = "Cross-Platform-VulkanGFX"
    version = "0.0.1b"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    options = {"shared": [True, False]}
    default_options = {
        "shared": True,
    }

    def requirements(self):
        self.requires("glm/cci.20230113")
        self.requires("glfw/3.3.8")
        if self.settings.os == "Macos":
            self.requires("moltenvk/1.2.2")
        else:
            self.requires("vulkan-loader/1.3.239.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        if self.settings.os == "Macos":
            fix_apple_shared_install_name(self)
        
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=True)
        self.copy("*.dll", dst="bin", keep_path=True)
        self.copy("*.dylib*", dst="lib", keep_path=True)
        self.copy("*.so", dst="lib", keep_path=True)
        self.copy("*.a", dst="lib", keep_path=True)

    def package_info(self):
        self.cpp_info.includedirs = ["include", "src/include", "lib/include"]

    def build_requirements(self):
        self.build_requires("cmake/3.22.6")
