# Computational Geometry Course Project 
![APM](https://img.shields.io/apm/l/vim-mode)

## Scope
Project for the course of Computational Geometry 2020/2021 @UNIMI

This project was developed with the intent of study different techniques for the triangulations and tessellations of geometric shapes with OpenGL.

## Dependencies
- GLFW
- GLEW

Both of these libraries are integrated with CONAN, you must have installed ![CMake](https://cmake.org/download/) and ![CONAN](https://conan.io/downloads.html), then follow the installation instructions.

## Install

1. Access by terminal to the folder *'Computational_Geometry'*.
2. Then run this command:

```cmake src -DCMAKE_BUILD_TYPE=Release -B ../build/```

3. Once the process is over move to the folder *'../build'*, and run this command:

```make```

4. Once the building is over, copy the executable file *'/bin/Application'* inside the folder  *'Computational_Geometry_2021/Computational_Geometry/'*.

5. Move to the folder where it is the executable now, in *'Computational_Geometry_2021/Computational_Geometry/'*.

6. Run the command:

```./bin/Application```
