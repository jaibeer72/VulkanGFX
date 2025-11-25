//
//  Window.hpp
//  VulkanGFX
//
//  Created by Jaibeer Dugal on 08/09/2023.
//

#ifndef Window_hpp
#define Window_hpp

#include <GLFW/glfw3.h>
#include <string>

#include "../Core/Public/ModuleCoreInterface.hpp"

// Lightweight Window wrapper around GLFW.
// Ownership and responsibilities:
// - Window owns the `GLFWwindow*` and is responsible for creating/destroying it.
// - The renderer (VulkanRenderer) *uses* the GLFW window to create a surface and query required extensions.
// - Window does NOT depend on the renderer.
class Window : public IModuleBaseInterface {
public:
    Window(uint32_t width = 800, uint32_t height = 600, const std::string& title = "Vulkan");
    ~Window();

    // Explicit lifecycle control compatible with the IModuleBaseInterface.
    void InitializeModule() override;
    void UpdateModule() override;
    void CleanUpModule() override;

    // Convenience API used by the rest of the engine / renderer.
    bool initialize();
    void pollEvents();
    bool shouldClose() const;
    void destroy();

    GLFWwindow* getHandle() const { return window_; }
    uint32_t width() const { return width_; }
    uint32_t height() const { return height_; }

private:
    GLFWwindow* window_{nullptr};
    uint32_t width_;
    uint32_t height_;
    std::string title_;
};

#endif /* Window_hpp */
