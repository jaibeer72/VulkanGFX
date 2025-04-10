# Build status on main
![Mac OS Xcode File gen and Build exe](https://github.com/jaibeer72/VulkanGFX/actions/workflows/build_Xcode_Proj.yml/badge.svg?branch=main)
![Windows VS17(2022) SLN gen and Build exe](https://github.com/jaibeer72/VulkanGFX/actions/workflows/build_VS_Solution.yml/badge.svg?branch=main)

# Vulkan-based modular graphics engine
# IMPORTANT INFOMRATION ! 
- we might be using moltenVK on the mac side of things.


## Goals of the project

- basic 3D/2D rendering first 
- Cross-platform compilations Current support Windows VSstudio 17 year 2022 and Xcode mac 
- 2D UI system with Dom controls in a separate project 
- Toolkit launcher
- (to consider) binary builds so that we can just incorporate it into other projects to marshal them into C# frontEnds that can use MVC based UI's or single applications. 


# Requriments to run 
- You should be able to just run the MakeProject.bat for Windows or MakeProject.sh for Mac but i am still working on them so 
## Expternal Dependencies 
- Cmake 

# How to build 
## requirements 
- cmake

- working updates vcpkg being used for cross platofmr 
- mac os Requimentens ```brew install pkg-config```
- install the requirements using ```./vcpkg/vcpkg install```
- then build the project using ```cmake -B build -S .```
- ```cmake --build build ```


# [look at Conventions](./Docs/Conventions.md)

# [!To see devlog and notes view WIKI](https://github.com/jaibeer72/VulkanGFX/wiki)


# Dev help 

## VSCode launch settings for Debugging using lldb-dap 

- Extention required lldb-dap 

```json 
     "configurations": [
        {
            "name": "Debug Vulkan App",
            "type": "lldb-dap",
            "request": "launch",
            "program": "${workspaceFolder}/build/VulkanGFX", // Path to your output binary
            "args": [], // Add any command-line arguments your program needs
            "cwd": "${workspaceFolder}", // Set the working directory to the project root
            "stopAtEntry": false, // Set to true if you want to stop at the program's entry point
            "environment": [], // Add any environment variables if needed
            "internalConsoleOptions": "openOnSessionStart",
            "miDebuggerPath": "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lldb" 
        }
    ]
```



