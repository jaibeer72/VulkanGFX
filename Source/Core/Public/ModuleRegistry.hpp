//
// Created by Jaibeer Dugal on 09/09/2023.
//

#ifndef CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP
#define CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>
#include <typeinfo>

class IModule;

class ModuleRegistry {
public:
    static ModuleRegistry& Instance() {
        static ModuleRegistry instance;
        return instance;
    }

    template<typename T>
    void RegisterModule(std::shared_ptr<T> instance, const std::string& moduleName, const std::vector<std::string>& moduleDependencies) {
        modules[std::type_index(typeid(T))].emplace(moduleName, instance);
        dependencies[moduleName] = moduleDependencies;
    }

    template<typename T>
    T* GetModule(const std::string& moduleName) const {
        auto moduleTypeIt = modules.find(std::type_index(typeid(T)));
        if (moduleTypeIt != modules.end()) {
            const auto& moduleInstances = moduleTypeIt->second;
            auto instanceIt = moduleInstances.find(moduleName);
            if (instanceIt != moduleInstances.end()) {
                return dynamic_cast<T*>(instanceIt->second.get());
            }
        }
        return nullptr;
    }

private:

    void InitializeModules();

    void UpdateModules();

    void CleanUpModules();

    std::vector<IModule*>  SortModulesByDependencies();

private:
    // setting module dirty as soon as it changes
    bool IsDirty = false;
    // Use a type_index as the key to store modules of the same type
    std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<IModule>>> modules;
    std::unordered_map<std::string, std::vector<std::string>> dependencies;
};
#endif //CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP
