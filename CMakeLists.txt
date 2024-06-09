cmake_minimum_required(VERSION 3.27)
project(aip_project_2_buhs)

set(CMAKE_CXX_STANDARD 20)

add_executable(aip_project_2_buhs main.cpp
        program.cpp
        program.h
        data_reader.cpp
        data_reader.h
        TrainingLoop.cpp
        TensorsNet.cpp
        TrainingLoop.h
        TensorsNet.h
        matrix.cpp
        matrix.h)
