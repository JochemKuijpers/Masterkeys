# Masterkeys

This repository contains code for a program to control the Coolermaster Masterkeys keyboards.
Currently supported are the Masterkeys Pro S/M/L keyboards with US layout. Both RGB and white LED versions are supported, but since I own a white LED version, RGB remains untested.

# Effects

The repository contains some effects (implementing classes of the `KeyboardEffect` interface). New effects can be created by implementing this interface and can be added to the system in the `main.cpp` file.

# Compiling

The project can be compiled using the CMake tools integrated in Visual Studio Community Edition or with some effort, with CLion using the Microsoft Visual C++ Compiler toolchains.

## Visual Studio

Clone or otherwise download the repository.

In Visual Studio, `Open Folder...` and select the root of the repository, where `CMakeList.txt` is located.

Select build target `x64 Release`, and build.

The binary can typically be found in `C:\Users\USER\CMakeBuilds\`. When moving the software, be sure to copy the `data` directory and the `SDKDLL.dll` file.
