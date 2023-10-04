//
// Created by Jaibeer Dugal on 09/09/2023.
//

#include "../Public/ModuleRegistry.hpp"

#define REGISTER_MODULE(ModuleClass, ModuleName, ...)\
namespace { \
    struct ModuleClass##Registrar { \
        ModuleClass##Registrar() { \
            static std::shared_ptr<ModuleClass> ModuleName = std::make_shared<ModuleClass>(); \
            ModuleRegistry::Instance().RegisterModule(ModuleName, #ModuleName,{__VA_ARGS__}); \
        } \
    }; \
    static ModuleClass##Registrar ModuleClass##registrar; \
}



