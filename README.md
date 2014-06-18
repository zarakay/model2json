ply2json
========

PLY File Format to JSON Converter for use with Three.js

Using this program, a standard ply file can be converted into a JSON file which is compatible for loading into Three.js

# How to Build

Below are the requirements and steps to build the program

## Requirements
  
  The following requirements must be available in the system in order to build and run the program
  
* [VTK Toolkit Shared Libraries] (www.vtk.org)
* [CMake] (www.cmake.org) 

## Build Commands

Firstly it is best to create a build folder since attempting to build in the source directory can cause problems. Once in the correct directory, cmake has to be used in order to create the make file for your system. Then the program can be built. The following commands will do this for you:


```
mkdir build
cd build
cmake ..
make
```

If the above commands ran successfuly then you have successfully built ply2json. Congradulations!

The are several ways to customize the build process with cmake, please look at the vtk website for the customizations.

# How to Run

In order to run the program, the is used.

```
ply2json filename.ply outputfile
```

The program should output `outputfile.json` which can be used with Three.js to visualize the browser. 

