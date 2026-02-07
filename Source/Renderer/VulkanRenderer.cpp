#include "VulkanRenderer.hpp"
#include <iostream>

VulkanRenderer::VulkanRenderer() {}

VulkanRenderer::~VulkanRenderer() {
    cleanup();
}

void VulkanRenderer::initialize(GLFWwindow* window) {
    // Check if GLFW supports Vulkan
    if (!glfwVulkanSupported()) {
        throw std::runtime_error("GLFW reports Vulkan is not supported on this system!");
    }
    std::cout << "GLFW Vulkan support: OK\n";

    if (!instance) {
        createInstance();
    }

    if (window && !surface) {
        createSurface(window);
    }
}

void VulkanRenderer::cleanup() {
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
        surface = VK_NULL_HANDLE;
    }
    destroyInstance();
}

void VulkanRenderer::createInstance() {
    if (instance) return;

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanGFX";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    if (!glfwExtensions) {
        throw std::runtime_error("glfwGetRequiredInstanceExtensions failed! Vulkan might not be available.");
    }

    std::cout << "GLFW required extensions (" << glfwExtensionCount << "):" << std::endl;
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        std::cout << "  " << glfwExtensions[i] << std::endl;
    }

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
#if __APPLE__
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        std::cerr << "vkCreateInstance failed with error code: " << result << std::endl;
        throw std::runtime_error("failed to create Vulkan instance!");
    }
    std::cout << "Vulkan instance created successfully\n";
}

void VulkanRenderer::createSurface(GLFWwindow* window) {
    if (!instance) throw std::runtime_error("createSurface: instance not created");
    if (surface != VK_NULL_HANDLE) return;

    std::cout << "Creating Vulkan surface..." << std::endl;
    std::cout << "  Instance: " << instance << std::endl;
    std::cout << "  Window: " << window << std::endl;

    VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
    if (result != VK_SUCCESS) {
        std::cerr << "glfwCreateWindowSurface failed with error code: " << result << std::endl;
        throw std::runtime_error("failed to create window surface!");
    }
    std::cout << "Surface created successfully: " << surface << std::endl;
}

void VulkanRenderer::destroyInstance() {
    if (instance) {
        vkDestroyInstance(instance, nullptr);
        instance = VK_NULL_HANDLE;
    }
}
