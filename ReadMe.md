# VulkanGFX

![Mac OS Xcode File gen and Build exe](https://github.com/jaibeer72/VulkanGFX/actions/workflows/build_Xcode_Proj.yml/badge.svg?branch=main)
![Windows VS17(2022) SLN gen and Build exe](https://github.com/jaibeer72/VulkanGFX/actions/workflows/build_VS_Solution.yml/badge.svg?branch=main)

A cross-platform, Vulkan-based modular graphics engine.

## Goals

- Basic 3D/2D rendering capabilities
- Cross-platform support (Windows, Linux, macOS)
- 2D UI system with DOM controls (separate project)
- Toolkit launcher
- Binary builds for integration into C# frontends

## Important Notes

- **macOS**: Uses MoltenVK for Vulkan support
- **vcpkg**: All dependencies are managed via vcpkg submodule

---

## Getting Started

### Prerequisites

All platforms require:
- **CMake** 3.21 or higher
- **Git** (with submodule support)
- **C++17** compatible compiler

### Clone the Repository

```bash
git clone --recursive https://github.com/jaibeer72/VulkanGFX.git
cd VulkanGFX
```

If you forgot `--recursive`:
```bash
git submodule update --init --recursive
```

---

## Platform-Specific Requirements

### 🐧 Linux

**Required packages:**
```bash
# Arch Linux
sudo pacman -S base-devel cmake ninja curl zip unzip tar git

# Ubuntu/Debian
sudo apt-get install build-essential cmake ninja-build curl zip unzip tar git \
    libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config

# Fedora
sudo dnf install @development-tools cmake ninja-build curl zip unzip tar git \
    libXinerama-devel libXcursor-devel libXrandr-devel libXi-devel mesa-libGL-devel
```

**Supported Generators:**
- `linux-ninja` (recommended) - Ninja build system

**Bootstrap vcpkg:**
```bash
bash vcpkg/bootstrap-vcpkg.sh
```

### 🪟 Windows

**Required tools:**
- Visual Studio 2022 (or 2019) with C++ Desktop Development workload
- CMake (included with Visual Studio or standalone)

**Supported Generators:**
- `VisualStudio` - Visual Studio 2022
- `MinGW` - MinGW Makefiles

**Bootstrap vcpkg:**
```powershell
.\vcpkg\bootstrap-vcpkg.bat
```

### 🍎 macOS

**Required tools:**
```bash
brew install cmake ninja pkg-config
```

**Optional Vulkan runtime helpers (recommended for local debugging):**
```bash
brew install vulkan-tools
```

- `vulkan-loader` is **not required** for this project build, because Vulkan is provided through `vcpkg` (`find_package(Vulkan REQUIRED)`).
- `vulkan-tools` provides the mock ICD JSON on macOS, which is useful if your local Vulkan runtime setup is incomplete.

**Supported Generators:**
- `osx-xcode` - Xcode project generation

**Bootstrap vcpkg:**
```bash
bash vcpkg/bootstrap-vcpkg.sh
```

---

## Building the Project

### Using CMake Presets (Recommended)

The project includes CMake presets for all platforms:

**Linux:**
```bash
cmake --preset linux-ninja
cmake --build --preset linux-ninja:Debug
```

**Windows (Visual Studio):**
```powershell
cmake --preset VisualStudio
cmake --build --preset VisualStudio:Debug
```

**Windows (MinGW):**
```powershell
cmake --preset MinGW
cmake --build --preset MinGW:Debug
```

**macOS:**
```bash
cmake --preset osx-xcode
cmake --build --preset osx-xcode:Debug
```

### Manual Build

If you prefer not to use presets:

```bash
# Configure
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build
```

### Available Build Presets

- `VulkanGFX:Debug` - Default debug configuration
- `linux-ninja:Debug` - Linux with Ninja
- `VisualStudio:Debug` - Windows with Visual Studio
- `MinGW:Debug` - Windows with MinGW
- `osx-xcode:Debug` - macOS with Xcode

---

## Running the Application

After building, the executable will be located at:

- **Linux/Mac**: `out/build/<preset-name>/VulkanGFX`
- **Windows**: `out/build/<preset-name>/Debug/VulkanGFX.exe`


---

## Dependencies

All dependencies are automatically managed by vcpkg:

- **GLFW** 3.4 - Window and input handling
- **GLM** 1.0.2 - Mathematics library
- **Vulkan SDK** 1.4.328 - Graphics API

---

## Documentation

- **[Coding Conventions](./Docs/Conventions.md)** - Project coding standards
- **[Development Log & Notes](https://github.com/jaibeer72/VulkanGFX/wiki)** - Wiki with detailed notes

---

## Development

### Debugging with VSCode

**Required Extension:** `lldb-dap` (for macOS/Linux) or `ms-vscode.cpptools` (for all platforms)

**Example launch.json configuration (macOS with lldb-dap):**

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Vulkan App",
            "type": "lldb-dap",
            "request": "launch",
            "program": "${workspaceFolder}/out/build/osx-xcode/Debug/VulkanGFX",
            "args": [],
            "cwd": "${workspaceFolder}",
            "stopAtEntry": false,
            "environment": [],
            "internalConsoleOptions": "openOnSessionStart",
            "miDebuggerPath": "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/lldb"
        }
    ]
}
```

**For Linux:**
```json
{
    "name": "Debug Vulkan App (Linux)",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/out/build/linux-ninja/VulkanGFX",
    "args": [],
    "cwd": "${workspaceFolder}",
    "environment": [],
    "externalConsole": false,
    "MIMode": "gdb",
    "setupCommands": [
        {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
        }
    ]
}
```

**For Windows:**
```json
{
    "name": "Debug Vulkan App (Windows)",
    "type": "cppvsdbg",
    "request": "launch",
    "program": "${workspaceFolder}/out/build/VisualStudio/Debug/VulkanGFX.exe",
    "args": [],
    "cwd": "${workspaceFolder}",
    "environment": [],
    "console": "integratedTerminal"
}
```

---

## Troubleshooting

### Linux: Permission denied when running executables

If your workspace is on a separate partition mounted with `noexec`, remount it:

```bash
sudo mount -o remount,exec /path/to/workspace
```

To make it permanent, edit `/etc/fstab` and add `exec` to the mount options.

### vcpkg bootstrap fails

Ensure you have all required tools installed for your platform (see Platform-Specific Requirements above).

### Missing Vulkan drivers

- **Linux**: Install your GPU vendor's Vulkan drivers (mesa-vulkan-drivers, nvidia-utils, etc.)
- **Windows**: Update your GPU drivers from manufacturer's website
- **macOS**: MoltenVK is included via vcpkg

---

## License

See [LICENSE.txt](LICENSE.txt) for licensing information.

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) if available, or open an issue to discuss proposed changes.



