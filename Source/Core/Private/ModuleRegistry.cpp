//
// Created by Jaibeer Dugal on 09/09/2023.
//



#include "../Public/ModuleRegistry.hpp"
#include "../Public/ModuleCoreInterface.hpp"


void ModuleRegistry::InitializeModules() {
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

template<typename T>
void ModuleRegistry::RegisterModule(T *instance) {
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
