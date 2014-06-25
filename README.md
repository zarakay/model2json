model2json
========

3D Model File Format to JSON Converter for use with Three.js

Using this program, a 3D model file can be converted into a JSON file which is compatible for loading into Three.js
The program also allows you to decimate the 3D models file and reduce to quality of the model. 

###File Support

* Polygon File Format (PLY)



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

If the above commands ran successfully then you have successfully built model2json. Congratulations!

The are several ways to customize the build process with cmake, please look at the vtk website for the customizations.

# How to Run

In order to run the program, the is used.

```
model2json [-t] [-s] [-b] [-v] [-d 0.0 .. 1.0] filename output
```

```
-t          Preserve topology
-s          Enable splitting
-b          Enable boundary vertex deletion
-v          Verbose
-d 0.0..1.0 Decimation amount (maximum 1.0)
filename    File to convert
output      Output file
```
