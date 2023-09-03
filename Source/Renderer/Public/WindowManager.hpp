//
//  WindowManager.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 24/08/2023.
//

#ifndef WindowManager_hpp
#define WindowManager_hpp

#include "../../Core/Public/ModuleCoreInterface.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class WindowManager : IModuleBaseInterface
{
public:
    void InitializeModule() override;
    void UpdateModule() override;
    void CleanUpModule() override;
private:
    bool InitailizeWindow();
// making this protected now might need to inject this later.
protected:
    GLFWwindow* window;
private:
    const uint32_t WindowWidth = 800;
    const uint32_t WindowHeight = 600;
    
};

#endif /* WindowManager_hpp */
