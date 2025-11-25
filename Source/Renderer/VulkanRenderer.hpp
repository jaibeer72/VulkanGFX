// VulkanRenderer.hpp
// Lightweight Vulkan renderer encapsulating VkInstance and surface creation
//
// Lifecycle and instancing:
// - The renderer owns the VkInstance and any Vulkan objects it creates (e.g. VkSurfaceKHR and beyond).
// - The application owns the Window and passes a `GLFWwindow*` to the renderer so it can create a surface.
// - Instance must be created before creating the surface.
// - The order during shutdown is the reverse: destroy surface, then destroy instance.
#ifndef VulkanRenderer_hpp
#define VulkanRenderer_hpp

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
class VulkanRenderer {
public:
    VulkanRenderer();
    ~VulkanRenderer();

    // Initialize and clean up the renderer. The renderer uses the window handle
    // to create a Vulkan surface, but it DOES NOT take ownership of the window
    // lifecycle.
    void initialize(GLFWwindow* window);
    void cleanup();

    VkInstance getInstance() const { return instance; }
    VkSurfaceKHR getSurface() const { return surface; }

private:
    void createInstance();
    void createSurface(GLFWwindow* window);
    void destroyInstance();

    VkInstance instance{VK_NULL_HANDLE};
    VkSurfaceKHR surface{VK_NULL_HANDLE};
};

#endif /* VulkanRenderer_hpp */
