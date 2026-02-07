#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "Window/Window.hpp"
#include "Renderer/VulkanRenderer.hpp"
#include "Input/InputManager.hpp"

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