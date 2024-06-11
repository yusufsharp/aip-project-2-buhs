cmake_minimum_required(VERSION 3.27)
project(aip_project_2_buhs)

set(CMAKE_CXX_STANDARD 20)

add_executable(aip_project_2_buhs main.cpp
        neural_net.cpp
        neural_net.h
        program.cpp
        program.h
        data_reader.cpp
        data_reader.h
        TensorsNet.cpp
        TensorsNet.h
        matrix.cpp
        matrix.h
        data_reader.cpp
        TrainingLoop.cpp
        TrainingLoop.h
)

