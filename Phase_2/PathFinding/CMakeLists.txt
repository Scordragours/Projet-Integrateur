cmake_minimum_required(VERSION 3.12)
project(PathFinding)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PathFinding
        .idea/codeStyles/Project.xml
        .idea/encodings.xml
        .idea/misc.xml
        .idea/modules.xml
        .idea/PathFinding.iml
        .idea/workspace.xml
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/PathFinding.cbp
        cmake-build-debug/PathFinding.exe
        CMakeLists.txt
        library.cpp
        library.h
        Point_T.cpp
        Point_T.h)
