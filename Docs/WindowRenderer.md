## Window & VulkanRenderer Usage

This document explains the ownership and basic usage of `Window` and `VulkanRenderer` classes。

Summary:
- `Window` encapsulates GLFW. It owns the `GLFWwindow*` and is responsible for creating and destroying it.
- `VulkanRenderer` encapsulates Vulkan initialization steps such as `VkInstance` creation and `VkSurfaceKHR` creation.
- `VulkanRenderer` does not own the `GLFWwindow`; it receives a pointer to create an OS-specific surface.

Typical usage pattern (in `main`):

1. Construct a `Window` and initialize it.
2. Create a `VulkanRenderer` instance and call `initialize(window.getHandle())`.
3. Run the main loop, calling `window.pollEvents()`.
4. On exit, call `renderer.cleanup()` followed by `window.destroy()`.

Order of cleanup matters: destroy renderer resources (surface, VkInstance, Vulkan objects) before destroying the window.

Example:
```cpp
Window window(800, 600, "VulkanGFX");
if (!window.initialize()) return -1;

VulkanRenderer renderer;
renderer.initialize(window.getHandle());

while (!window.shouldClose()) {
    window.pollEvents();
}

renderer.cleanup();
window.destroy();
```

Rationale behind the split:
- This split keeps platform-windowing code (GLFW) independent from the rendering backend (Vulkan). In the future, you can add other renderer types (Metal, DirectX, OpenGL) without changing the window layer.
- The `Window` class acts like an OS abstraction and is safe to construct/destroy regardless of which renderer is used.

-- End
