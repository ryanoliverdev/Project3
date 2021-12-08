cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MenuMaker)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
set(TGUI_DIR "C:/TGUI/lib/cmake/TGUI")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(TGUI REQUIRED)

add_executable(MenuMaker main.cpp Algorithm.h Graph.h)
target_link_libraries(MenuMaker tgui sfml-graphics sfml-audio)