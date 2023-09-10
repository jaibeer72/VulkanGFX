//
//  ModuleCoreInterface.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 24/08/2023.
//

#ifndef ModuleCoreInterface_hpp
#define ModuleCoreInterface_hpp

#include <iostream>
#include <unordered_map>
#include <vector>

class IModule {
public:
    virtual void InitializeModule() = 0;
    virtual void UpdateModule() = 0;
    virtual void CleanUpModule() = 0;
    virtual std::vector<std::string> GetDependencies() const = 0;
    virtual void SetDependencies(const std::unordered_map<std::string, IModule*>& dependencies) = 0;
};

#endif /* ModuleCoreInterface_hpp */
