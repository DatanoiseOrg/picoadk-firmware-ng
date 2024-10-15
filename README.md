# PicoADK NG Firmware

This is a work-in-progress rework of the Datanoise PicoADK V2 firmware template
with a bigger focus on modularity.

While it can be used with other Raspberry RP235x based board, it is stongly
recommended to be used with the PicoADK V2.

## Prerequisites

### MacOS
To build this project, you need to install the following tools:
On macOS (using Homebrew)

Install Homebrew (if not installed):

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Install the required tools:

```bash
brew install cmake gcc-arm-embedded git cpplint
```

### Debian/Ubuntu

Update and install the required packages:

```bash
sudo apt update
sudo apt install cmake gcc-arm-none-eabi build-essential git cppint
```


# Windows
Follow the instructions for Debian/Ubuntu inside your WSL instance.

## Building

Clone the PicoADK NG Firmware repository:

```bash
git clone https://github.com/DatanoiseTV/PicoADK-NG-Firmware.git
cd PicoADK-NG-Firmware

Create a build directory:

```bash
mkdir build
cd build
```

Run CMake to generate the build system:

```bash
cmake ..
```

Build the project:

```bash
    make ( Add -j to build in parallel using all your CPU cores )
```

This will create the firmware binaries in the build directory.

## Flashing

You can use any standard method to flash the generated .uf2 file onto your PicoADK V2 board, such as dragging and dropping the file onto the mounted drive after entering bootloader mode.

## Project Structure

Here is an overview of the directory structure and the key files in this repository:
```
  ├── README.md            # This file, describing the project structure
  ├── .githooks            # Custom hooks for Git to lint code etc.
  ├── .github              # GitHub CI/CD configuration
  ├── CMakeLists.txt       # Main CMake configuration file
  ├── project_config.cmake # Additional project-specific configuration
  ├── build/               # Directory where build artifacts are stored
  ├── cmake/               # CMake scripts for handling SDK and dependencies
  ├── include/             # Global header files for user includes
  ├── src/                 # Application source files (main application logic)
  └── core/                # Core library and drivers for the project
   |___ lib/               # Additional libraries for the core
   |___ src/               # Core system source files
   |___ include/           # Core system includes such as FreeRTOS configuration etc.
```