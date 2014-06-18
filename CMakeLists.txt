cmake_minimum_required(VERSION 2.8)
 
PROJECT(ply2json)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadPLY MACOSX_BUNDLE ReadPLY)
 
if(VTK_LIBRARIES)
      target_link_libraries(ReadPLY ${VTK_LIBRARIES})
  else()
        target_link_libraries(ReadPLY vtkHybrid vtkWidgets)
    endif()
