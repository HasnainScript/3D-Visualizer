cmake_minimum_required(VERSION 3.20)
project(ParametricCAD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# VTK from vcpkg
find_package(VTK REQUIRED COMPONENTS 
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersSources
    vtkRenderingCore
    vtkInteractionStyle
    vtkRenderingOpenGL2
)

add_executable(ParametricCAD src/main.cpp)

target_link_libraries(ParametricCAD PRIVATE ${VTK_LIBRARIES})

# This initializes the rendering modules (required for VTK 9+)
vtk_module_autoinit(
    TARGETS ParametricCAD
    MODULES ${VTK_LIBRARIES}
)
