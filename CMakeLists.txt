cmake_minimum_required(VERSION 3.20)
project(aip_project_2_buhs)

set(CMAKE_CXX_STANDARD 20)


add_executable(paint_app neural_net.cpp
        neural_net.h
        program.cpp
        program.h
)

#для работы холста
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(paint_app sfml-graphics sfml-window sfml-system)