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
};

#endif /* ModuleCoreInterface_hpp */
