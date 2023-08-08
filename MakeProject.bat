@echo off

@REM REM Create the build directory if it doesn't exist
@REM if not exist build mkdir build
@REM cd build

@REM check if pip is installed 
if not exist pip (
    echo pip is not installed. 
    @REM install pip 
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    python get-pip.py
)

@REM Check if conan is installed
if not exist conan (
    echo conan is not installed. 
    @REM install conan 
    pip install conan
)
@REM Check if conan is installed sucessfully
if not exist conan (
    echo conan is not installed sucessfully. 
    pause
    exit
)

@REM Check if conan profile is exist
conan profile detect
@REM run conan install command
conan install . -s build_type=Debug -c tools.cmake.cmaketoolchain:generator="Visual Studio 17 2022" --output-folder=ProjectFolder --build missing

@REM check if install was sucessful
if not exist ProjectFolder (
    echo conan install was not sucessful. 
    pause
    exit
)

cd ProjectFolder

REM Generate the Visual Studio solution
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -G "Visual Studio 17 2022" ..

echo Visual Studio solution generated in the build directory.
pause
