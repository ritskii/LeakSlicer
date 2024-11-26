cmake_minimum_required(VERSION 3.28)
project(LeakSlicer)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/OpenSTL-main/modules/core/include)

add_executable(LeakSlicer main.cpp
        Importer.hpp
        Importer.hpp
        Model.hpp
        Importer.hpp)
