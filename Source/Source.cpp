#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <string>

#include "Window/Window.hpp"
#include "Renderer/VulkanRenderer.hpp"
#include "Input/InputManager.hpp"

#if __APPLE__
static void ConfigureMacOSVulkanIcd() {
    const char* existing = std::getenv("VK_ICD_FILENAMES");
    if (existing && *existing) {
        return;
    }

    std::vector<std::string> prefixes;
    if (const char* brewPrefix = std::getenv("HOMEBREW_PREFIX"); brewPrefix && *brewPrefix) {
        prefixes.emplace_back(brewPrefix);
    }
    prefixes.emplace_back("/opt/homebrew");
    prefixes.emplace_back("/usr/local");

    for (const auto& prefix : prefixes) {
        const std::filesystem::path icdPath =
            std::filesystem::path(prefix) / "opt" / "vulkan-tools" / "lib" / "mock_icd" / "VkICD_mock_icd.json";

        if (std::filesystem::exists(icdPath)) {
            setenv("VK_ICD_FILENAMES", icdPath.c_str(), 1);
            std::cout << "Using Vulkan mock ICD: " << icdPath << std::endl;
            return;
        }
    }
}
#endif

int main() {
    try {
#if __APPLE__
        ConfigureMacOSVulkanIcd();
#endif

        // Create and initialize the window (owner of GLFW window handle)
        Window window(800, 600, "VulkanGFX");
        if (!window.initialize()) {
            std::cerr << "Failed to initialize window.\n";
            return EXIT_FAILURE;
        }

        // Create renderer and initialize using the existing window handle
        VulkanRenderer renderer;
        renderer.initialize(window.getHandle());

        // Create input manager and bind a simple action
        Input::InputManager input;
        input.initialize(window.getHandle());
        input.bindAction("Jump", GLFW_KEY_SPACE);
        input.bindAxis("MoveX", GLFW_KEY_D, GLFW_KEY_A);



        // Main loop: Poll for events until the window is closed
        while (!window.shouldClose()) {
            window.pollEvents();

            // Update input and query actions
            input.update();
            if (input.isActionPressed("Jump")) {
                std::cout << "Jump pressed\n";
            }
            float mx = input.getAxis("MoveX");
            if (mx != 0.f) {
                std::cout << "MoveX: " << mx << std::endl;
            }
        }

        // Cleanup (order matters: renderer should release Vulkan resources before destroying window)
        renderer.cleanup();
        window.destroy();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}