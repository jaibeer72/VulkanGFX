@echo off

REM Create the build directory if it doesn't exist
if not exist build mkdir build
cd build

REM Generate the Visual Studio solution
cmake -G "Visual Studio" ..

echo Visual Studio solution generated in the build directory.
pause
