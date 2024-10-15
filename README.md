# PicoADK NG Firmware

This is a work-in-progress rework of the Datanoise PicoADK V2 firmware template
with a bigger focus on modularity.

While it can be used with other Raspberry RP235x based board, it is stongly
recommended to be used with the PicoADK V2.

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