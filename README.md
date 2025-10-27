# Snake in C++ 🐍

## How to build using CMake

### Windows

cmake -B build/vs2022 -G "Visual Studio 17 2022"
cmake --build build/vs2022 --config Release

### Linux

cmake -B build/ninja-multi -G "Ninja Multi-Config"
cmake --build build/ninja-multi --config Release
