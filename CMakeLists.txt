cmake_minimum_required(VERSION 2.8)
 
PROJECT(model2json)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(model2json ply2json vtk2json model2json)
 
if(VTK_LIBRARIES)
        target_link_libraries(model2json ${VTK_LIBRARIES})
else()
        target_link_libraries(model2json vtkHybrid vtkWidgets)
endif()
