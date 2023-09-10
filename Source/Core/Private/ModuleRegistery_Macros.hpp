//
// Created by Jaibeer Dugal on 09/09/2023.
//

#define REGISTER_MODULE(ModuleClass, ...) \
namespace { \
    struct ModuleClass##Registrar { \
        ModuleClass##Registrar() { \
            static ModuleClass instance; \
            ModuleRegistry::Instance().RegisterModule(#ModuleClass, &instance); \
        } \
    }; \
    static ModuleClass##Registrar ModuleClass##registrar; \
}

