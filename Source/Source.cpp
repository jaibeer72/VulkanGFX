#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "Window/Window.hpp"
#include "Renderer/VulkanRenderer.hpp"

int main() {
    try {
        // Create and initialize the window (owner of GLFW window handle)
        Window window(800, 600, "VulkanGFX");
        if (!window.initialize()) {
            std::cerr << "Failed to initialize window.\n";
            return EXIT_FAILURE;
        }

        // Create renderer and initialize using the existing window handle
        VulkanRenderer renderer;
        renderer.initialize(window.getHandle());

        // Main loop: Poll for events until the window is closed
        while (!window.shouldClose()) {
            window.pollEvents();
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