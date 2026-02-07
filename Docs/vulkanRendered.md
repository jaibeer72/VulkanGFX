# THIS IS THE DAMN PIPELINE

![Figure 3.1 — Rendered Frame](./Figure_3.1_B18196.jpg)

*Figure 3.1 — Rendered Frame*


> Note: Vulkan is more explicit and verbose than OpenGL — it gives more control but requires more setup.

## Renderer Dock 🔧

- **OS Window** — The box on the screen that shows stuff. The OS keeps it open.
- **Vulkan Instance** — The phone line between your app and Vulkan. It lets them talk.
- **Vulkan Surface** — A special place the OS gives Vulkan to put the picture so the OS can show it.
- **Physical Device** — The real GPU hardware that makes pictures (can be 1 or more).
- **Queue Families** — Different lanes for jobs (drawing, computing). Like checkout lines.
- **Vulkan Device (Logical)** — A helper that talks to the physical GPU and holds the functions you use.
  - Note: One physical device can have more than one logical device.
- **Swapchain** — A queue of images; the app takes one, draws to it, and gives it back for display.
- **Image** — Memory that holds pixels (the picture itself).
- **ImageView** — Tells Vulkan how to look at an image (2D, depth, mipmaps).
- **Buffer** — A box of memory for data (vertices, colors, uniforms).
- **Framebuffer** — Where images are attached when drawing. We make one per swapchain image.
- **Command Pool & Command Buffer** — We record commands into buffers, then submit them to Vulkan. Can record on many threads.
- **Queue** — Where recorded commands are sent to be run by the GPU.
- **Shader** — Tiny programs that run on the GPU to decide colors and shapes (Vulkan uses precompiled shaders).
- **Render Pass** — A recipe that tells Vulkan which attachments and steps to use (can have subpasses).
- **Pipeline Layout** — Describes what inputs shaders get (textures, small per-draw data).
- **Rendering Pipeline** — Big set of rules for drawing (triangles/lines, blending, culling, depth, shaders).
- **Fences & Semaphores** — Sync tools: semaphores for GPU-to-GPU waiting, fences tell the CPU when the GPU finished.

Want this even simpler or drawn as pictures? Tell me which points to illustrate.

---

### Quick try — vk-bootstrap example ✅

I've added a small GLFW example that uses `vk-bootstrap` to create an instance, pick a GPU, create a device and a swapchain. Build with CMake (default ON):

- cmake -S . -B build
- cmake --build build --target vk_bootstrap_example

Run `./build/vk_bootstrap_example` to see the integration. It opens a window and prints the swapchain image count.

If you prefer vendoring or a submodule instead of vcpkg, tell me and I will switch the config.
