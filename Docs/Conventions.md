# These are going to be basic conventions for making new modules 

Ask your self these before adding a module and where 

- Core: Basic utilities, logging, and foundational classes.
- Platform: Platform-specific code (e.g., Windows, Linux, MacOS).
- Renderer: All Vulkan-specific code.
- Pipeline: Code related to Vulkan pipelines.
- Buffers: Vertex, index, uniform buffers, etc.
- Commands: Command buffers, command pools, etc.
- Window: Code related to window creation and management (e.g., using GLFW).
- Input: Handle user input.
- Scene: Scene management, entities, components, etc.
- Assets: Asset loading and management.

# Naming Conventions:
- Classes/Types: Use PascalCase (e.g., VertexBuffer, CommandPool).
- Functions/Methods: Use camelCase (e.g., initializeVulkan(), createCommandBuffers()).
- Variables: Use camelCase (e.g., vertexBuffer, commandPool).
- Constants: Use UPPER_SNAKE_CASE (e.g., MAX_FRAMES_IN_FLIGHT).
- Modules: Use PascalCase for module names and directories (e.g., Renderer, Input).
# Tips:
- Encapsulation: Keep data and implementation details private as much as possible. Expose only what's necessary through public interfaces.
- Forward Declarations: Use forward declarations to reduce dependencies between modules.
- Comments: Comment your code, especially the Vulkan-specific parts. Vulkan can be complex, and clear comments can help you and others understand the code better.
- Consistency: Whatever conventions or structures you decide on, be consistent. It makes the codebase easier to navigate and understand.
- Expandability: Design your modules with future expandability in mind. For instance, if you plan to support different rendering backends in the future (like DirectX or Metal), design your Renderer module to be abstracted away from the specific details of Vulkan.
  
# Future Modules:
As your project grows, I might add modules like:

- Physics: For physics simulation.
- Audio: For audio processing and playback.
- Networking: For multiplayer or other networked features.
- UI: For in-game user interfaces.