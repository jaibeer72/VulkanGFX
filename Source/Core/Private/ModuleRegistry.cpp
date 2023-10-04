//
// Created by Jaibeer Dugal on 09/09/2023.
//



#include "../Public/ModuleRegistry.hpp"
#include "../Public/ModuleCoreInterface.hpp"
#include <unordered_set>

void ModuleRegistry::InitializeModules() {
   // auto sortedModules = SortModulesByDependencies();
    for (const auto& [typeIndex, moduleMap] : modules) {
        for (const auto& [name, module] : moduleMap) {
            module->InitializeModule();
        }
    }
}

void ModuleRegistry::UpdateModules() {
    for (const auto& [typeIndex, moduleMap] : modules) {
        for (const auto& [name, module] : moduleMap) {
            module->UpdateModule();
        }
    }
}

void ModuleRegistry::CleanUpModules() {
    for (const auto& [typeIndex, moduleMap] : modules) {
        for (const auto& [name, module] : moduleMap) {
            module->CleanUpModule();
        }
    }
}

std::vector<IModule*> ModuleRegistry::SortModulesByDependencies() {
    IsDirty = true;

    std::vector<IModule*> sortedModules;
    std::unordered_map<std::string, bool> visited;

    std::function<void(const std::string&)> visit = [&](const std::string& moduleName) {
        if (visited.find(moduleName) == visited.end()) {
            visited[moduleName] = true;
            for (const auto& depName : dependencies[moduleName]) {
                visit(depName);
            }
            //sortedModules.push_back(modules[moduleName]);
        }
    };

    // Collect all modules and their dependencies in a set to ensure all are visited
//    std::unordered_set<std::string> allModules;
//    for (const auto& [name, module] : modules) {
//        allModules.emplace(name);
//    }
//
//    // Start visiting modules from those that are not dependencies for any module
//    for (const auto& [name, _] : modules) {
//        if (dependencies.find(name) == dependencies.end()) {
//            visit(name);
//        }
//    }
//
//    // Check if any modules are not visited (circular dependencies or missing dependencies)
//    for (const auto& moduleName : allModules) {
//        if (visited.find(moduleName) == visited.end()) {
//            // Handle error: Circular or missing dependency detected
//            // You can throw an exception or log an error here.
//        }
//    }

    return sortedModules;
}


