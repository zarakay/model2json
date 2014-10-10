model2json
========

3D Model File Format to JSON Converter for use with three.js

Using this program, a 3D model file can be converted into a JSON file which is compatible for loading into three.js
The program also allows you to decimate the 3D models file and reduce to quality of the model. 

###File Support

* Polygon File Format (PLY)
* Visualisation Toolkit (VTK)

## Requirements
  
The following system requirements are required to build and run the program:
  
* [VTK Toolkit Shared Libraries] (http://www.vtk.org)
* [CMake] (http://www.cmake.org) 

## Building

It is best to create a build folder outside of the source directory. Once in the build directory, CMake can be used to create a makefile, used for installing. The following commands will create an executable binary from the source:

```
mkdir build
cd build
cmake ..
make
```

If the above commands ran successfully then you have successfully built model2json. Congratulations!

The are several ways to customize the build process with cmake, please look at the vtk website for the customizations.

# Running

The usage and syntax is given below. The usage and syntax is given below. Note that a decimation value is always required, and must be specified with the `-d` flag.

```
model2json -d 0.0 .. 1.0 [-t] [-s] [-b] [-v] filename output
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
