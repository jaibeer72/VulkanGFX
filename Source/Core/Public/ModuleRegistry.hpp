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

    template<typename T>
    T* GetModule() const ;

    template<typename T>
    void RegisterModule(T* instance);

    void InitializeModules();

    void UpdateModules();

    void CleanUpModules();

private:
    std::unordered_map<std::string, IModule*> modules;
};


#endif //CROSS_PLATFORM_VULKANGFX_MODULEREGISTRY_HPP
