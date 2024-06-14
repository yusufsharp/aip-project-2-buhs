cmake_minimum_required(VERSION 3.20)
project(aip_project_2_buhs)

set(CMAKE_CXX_STANDARD 20)

# Установка пути к SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML/SFML")
set(CMAKE_MODULE_PATH "${SFML_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

# Включение директорий
include_directories(${SFML_INCLUDE_DIR})

# Добавление исполняемого файла проекта
add_executable(aip_project_2_buhs
        main.cpp
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
        TrainingLoop.cpp
        TrainingLoop.h
        predict.cpp
)

# Связывание с библиотеками SFML
target_link_libraries(aip_project_2_buhs sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# Добавление Google Test
add_subdirectory(external/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(external/googletest-main/googlemock/include)

# Добавление исполняемого файла для тестов
add_executable(runTestsApp
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
        TrainingLoop.cpp
        TrainingLoop.h
        predict.cpp
        testApp.cpp
)
add_executable(runTestsMatrix
        matrix.cpp
        matrix.h
        TensorsNet.cpp
        TensorsNet.h
        testMatrix.cpp
)
add_executable(runTestsPredict
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
        TrainingLoop.cpp
        TrainingLoop.h
        predict.cpp
        testPredict.cpp
)
# Связывание с библиотеками Google Test и SFML для тестов
target_link_libraries(runTestsApp gtest gtest_main sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(runTestsPredict gtest gtest_main gmock gmock_main sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(runTestsMatrix gtest gtest_main)
enable_testing()
# Добавление тестов в ctest
add_test(NAME runTestsApp COMMAND runTestsApp)
add_test(NAME runTestsMatrix COMMAND runTestsMatrix)
add_test(NAME runTestsPredict COMMAND runTestsPredict)