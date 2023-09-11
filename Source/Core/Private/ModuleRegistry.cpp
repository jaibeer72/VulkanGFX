//
// Created by Jaibeer Dugal on 09/09/2023.
//



#include "../Public/ModuleRegistry.hpp"
#include "../Public/ModuleCoreInterface.hpp"
#include <unordered_set>


void ModuleRegistry::InitializeModules() {
    
    auto sortedModules = SortModulesByDependencies();
    for (const auto& [name, module] : modules) {
        module->InitializeModule();
    }
}

void ModuleRegistry::UpdateModules() {
    for (const auto& [name, module] : modules) {
        module->UpdateModule();
    }
}

void ModuleRegistry::CleanUpModules() {
    for (const auto& [name, module] : modules) {
        module->CleanUpModule();
    }
}

std::vector<IModule*>  ModuleRegistry::SortModulesByDependencies() {

    IsDirty = true;

    std::vector<IModule*> sortedModules;
    std::unordered_set<std::string> visited;

    std::function<void(const std::string&)> visit = [&](const std::string& moduleName) {
        if (visited.find(moduleName) == visited.end()) {
            visited.insert(moduleName);
            for (const auto& depName : dependencies[moduleName]) {
                visit(depName);
            }
            sortedModules.push_back(modules[moduleName]);
        }
    };

    for (const auto& [name, module] : modules) {
        visit(name);
    }

    return sortedModules;
}

template<typename T>
void ModuleRegistry::RegisterModule(T *instance , const std::vector<IModule*>& dependencies) {
    modules[typeid(T).name()] = instance;
}

template<typename T>
T *ModuleRegistry::GetModule() const {
    const auto it = modules.find(typeid(T).name());
    if (it != modules.end()) {
        return dynamic_cast<T*>(it->second);
    }
    return nullptr;
}
