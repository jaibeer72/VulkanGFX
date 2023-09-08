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
- Conan 

# How to build 
## requirements 
- cmake 
- pip / will be installed by the run.sh file if possible (Sadly currently working on the Mac and I have yet to work on bat files. So not all edge cases have been considered. It's in the pipeline for September.)  

## how to build the Xcode project 
- in the folder running the command ```source MakeProject.sh``` should give you an easy way to build the project 

# [look at Conventions](./Docs/Conventions.md)

# [!To see devlog and notes view WIKI](https://github.com/jaibeer72/VulkanGFX.wiki.git)

