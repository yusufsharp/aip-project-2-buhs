cmake_minimum_required(VERSION 3.27)
project(aip_project_2_buhs)

set(CMAKE_CXX_STANDARD 20)



set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIBRARY_DIR "${SFML_DIR}/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

set(SFML_LIBRARIES
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
)

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

# Связывание с библиотеками SFML
target_link_libraries(aip_project_2_buhs ${SFML_LIBRARIES})

add_subdirectory(external/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(aip_project_2_buhs gtest gtest_main)