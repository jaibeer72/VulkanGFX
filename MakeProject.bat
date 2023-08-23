@echo off

@REM REM Create the build directory if it doesn't exist
@REM if not exist build mkdir build
@REM cd build

@REM check if pip is installed 
@REM if not exist pip (
@REM     echo pip is not installed. 
@REM     @REM install pip 
@REM     curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
@REM     python get-pip.py
@REM )
@REM Check if conan exists 

@REM check if pip exists else install pip 

pip -v 
if %ERRORLEVEL new 0(
    echo pip not found 
    python -m ensurepip --upgrade
)

conan -v 
if %ERRORLEVEL neq 0(
    echo conan not found
    pip install conan 
    @REM install Conan
)

@REM Check if conan profile exists
conan profile detect
if %ERRORLEVEL% neq 0 (
    echo Conan profile detection failed.
    @REM exit /b %ERRORLEVEL%
)

@REM Run conan install command
conan install . -c tools.cmake.cmaketoolchain:generator=visual_studio  --output-folder=ProjectFolder --build missing
if %ERRORLEVEL% neq 0 (
    echo Conan install failed.
    @REM exit /b %ERRORLEVEL%
)

@REM Check if install was successful
if not exist ProjectFolder (
    echo Conan install was not successful.
    @REM pause
    @REM exit /b 1
)

cd ProjectFolder

@REM Run conanbuild.bat
@REM ./conanbuild.bat

REM Generate the Visual Studio solution
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. 
if %ERRORLEVEL% neq 0 (
    echo CMake command failed.
    @REM exit /b %ERRORLEVEL%
)

echo Visual Studio solution generated in the build directory.
pause
