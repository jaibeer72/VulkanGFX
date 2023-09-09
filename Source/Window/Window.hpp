//
//  Window.hpp
//  VulkanGFX
//
//  Created by Jaibeer Dugal on 08/09/2023.
//

#ifndef Window_hpp
#define Window_hpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "../Core/Public/ModuleCoreInterface.hpp"

class Window : public IModuleBaseInterface
{
public:
    void InitializeModule() override;
    
    void UpdateModule() override;
    
    void CleanUpModule() override;

private:
    
};

#endif /* Window_hpp */
