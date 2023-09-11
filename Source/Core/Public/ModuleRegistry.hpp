//
// Created by Jaibeer Dugal on 09/09/2023.
//

#ifndef CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP
#define CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP

#include <vector>
#include <unordered_map>
#include <string>

class IModule;

class ModuleRegistry {
public:
    static ModuleRegistry& Instance() {
        static ModuleRegistry instance;
        return instance;
    }

private:
    // making function private
    template<typename T>
    T* GetModule() const ;

    template<typename T>
    void RegisterModule(T* instance , const std::vector<IModule*>& dependencies);

    void InitializeModules();

    void UpdateModules();

    void CleanUpModules();

    std::vector<IModule*>  SortModulesByDependencies();

private:
    // setting module dirty as soon as it changes
    bool IsDirty = false;
    std::unordered_map<std::string, IModule*> modules;
    std::unordered_map<std::string, std::vector<std::string>> dependencies;
};
#endif //CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP
