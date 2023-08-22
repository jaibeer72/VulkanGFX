//
//  Application.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 19/08/2023.
//

#ifndef Application_hpp
#define Application_hpp
#define GLFW_INCLUDE_VULKAN

#include<iostream>

class Application{
public:
    void run();
private:
    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void CleanUP();
    void CreateInstance();
};

#endif /* Application_hpp */
