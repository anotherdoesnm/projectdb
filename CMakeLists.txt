cmake_minimum_required(VERSION 3.15)
project(projectdb CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(OpenXLSX REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME}
src/main.cpp
src/mainwindow.cpp
src/dialog.cpp
src/exportexcel.cpp
include/mainwindow.h
include/dialog.h
include/exportexcel.h
ui/mainwindow.ui
ui/dialog.ui
ui/exportexcel.ui
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenXLSX::OpenXLSX)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Sql)