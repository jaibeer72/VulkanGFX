//
// Created by Jaibeer Dugal on 09/09/2023.
//

#include "../Public/ModuleRegistry.hpp"

/* TODO : List of things here
 Documentation: Add comments or documentation to the macro to explain its purpose and usage. This will help other developers understand how to use it correctly.
 Error Handling: Implement error handling within the macro. Currently, if std::make_shared<ModuleClass>() or ModuleRegistry::Instance().RegisterModule fails, there's no error handling. You can use a try-catch block to catch exceptions and handle errors appropriately.
 Circular Dependency Detection: Implement circular dependency detection within the SortModulesByDependencies function. This function should be able to handle cases where circular dependencies exist among modules.
 Logging/Reporting: Include logging or reporting mechanisms to inform developers about any issues related to module registration or dependency resolution. This will help in debugging and identifying problems during development.
 Testing: Create test cases to verify that the macro works as expected. Test various scenarios, including modules with and without dependencies, circular dependencies, and error conditions.
 Namespace Safety: Ensure that your macro works well within namespaces. Verify that it correctly resolves the module's name within the appropriate namespace.
 Dependency Handling: Make sure that the macro handles dependencies correctly. It should accept dependencies as variadic arguments and pass them to ModuleRegistry::RegisterModule.
 Memory Management: Consider memory management and lifetime of shared pointers. Ensure that modules are correctly managed and released when they are no longer needed.
 Naming Conventions: Choose clear and consistent naming conventions for modules and their dependencies. The use of #ModuleName as the module name in your macro is a good practice.
 Comments and Readability: Make your code as readable as possible. Add comments, whitespace, and formatting to enhance code clarity.
 Consistency: Ensure that the naming and usage of your macro are consistent throughout your codebase. Use it consistently to register modules.
 Performance: Consider the performance implications of your design, especially if you have a large number of modules. Optimize the code as needed.
 Error Messages: If there are errors during module registration, provide meaningful error messages that help developers identify the problem.
 Dependency Injection: Think about how modules interact with their dependencies and whether you need dependency injection mechanisms for modules.
 Exception Safety: Ensure that your code is exception-safe, especially when dealing with smart pointers and module registration.
 */

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



