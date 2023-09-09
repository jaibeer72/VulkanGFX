//
//  ModuleCoreInterface.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 24/08/2023.
//

#ifndef ModuleCoreInterface_hpp
#define ModuleCoreInterface_hpp

#include <stdio.h>

class IModuleBaseInterface {
protected:
    virtual void InitializeModule() = 0;
    virtual void UpdateModule() = 0;
    virtual void CleanUpModule() = 0;
};

#endif /* ModuleCoreInterface_hpp */
