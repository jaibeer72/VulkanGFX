//
//  ModuleCoreInterface.hpp
//  Cross-Platform-VulkanGFX
//
//  Created by Jaibeer Dugal on 24/08/2023.
//

#ifndef ModuleCoreInterface_hpp
#define ModuleCoreInterface_hpp

#include <stdio.h>

class ModuleBaseInterface {
public:
    void RunModule();
protected:
    virtual void InitializeModule();
    virtual void UpdateModule();
    virtual void CleanUpModule();
};

#endif /* ModuleCoreInterface_hpp */
