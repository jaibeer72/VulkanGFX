//
//  WindowManager.cpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 24/08/2023.
//

#include "../Public/WindowManager.hpp"
#include "../../Core/Public/SystemEvents.cpp"


void WindowManager::InitializeModule() {
    InitailizeWindow();
}

void WindowManager::UpdateModule() {
    glfwPollEvents();
    
    if(!glfwWindowShouldClose(window))
    {
        // This will throw an event to stop the modules to run 
        SystemEvents::SystemStopEvent.Invoke();
    }
}

void WindowManager::CleanUpModule() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool WindowManager::InitailizeWindow() {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Will handel resizeable later.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WindowWidth, WindowHeight, "Vulkan", nullptr, nullptr);
    return true; 
}
