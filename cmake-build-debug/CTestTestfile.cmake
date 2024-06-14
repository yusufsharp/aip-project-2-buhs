# CMake generated Testfile for 
# Source directory: /home/dima/programm_cpp/aip-project-2-buhs
# Build directory: /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[runTestsApp]=] "/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/runTestsApp")
set_tests_properties([=[runTestsApp]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;83;add_test;/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;0;")
add_test([=[runTestsMatrix]=] "/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/runTestsMatrix")
set_tests_properties([=[runTestsMatrix]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;84;add_test;/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;0;")
add_test([=[runTestsPredict]=] "/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/runTestsPredict")
set_tests_properties([=[runTestsPredict]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;85;add_test;/home/dima/programm_cpp/aip-project-2-buhs/CMakeLists.txt;0;")
subdirs("external/googletest-main")
