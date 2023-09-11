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

#include "../Core/Public/ModuleCoreInterface.hpp"
#include "../Config.hpp"
#include "../Core/Private/ModuleRegistery_Macros.hpp"
#include "../Core/Public/ModuleRegistry.hpp"


class Window : public IModule
{
public:
    void InitializeModule() override;
    void UpdateModule() override;
    void CleanUpModule() override;
    std::vector<std::string> GetDependencies() const override;
    void SetDependencies(const std::unordered_map<std::string, IModule*>& dependencies) override;

private:
    const uint32_t m_Width = Config::Window_Width;
    const uint32_t m_Height = Config::Window_Height;
};
REGISTER_MODULE(Window)
#endif /* Window_hpp */
