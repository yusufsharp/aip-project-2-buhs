# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/dima/clion-2023.3.4/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/dima/clion-2023.3.4/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dima/programm_cpp/aip-project-2-buhs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/aip_project_2_buhs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/aip_project_2_buhs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/aip_project_2_buhs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aip_project_2_buhs.dir/flags.make

CMakeFiles/aip_project_2_buhs.dir/main.cpp.o: CMakeFiles/aip_project_2_buhs.dir/flags.make
CMakeFiles/aip_project_2_buhs.dir/main.cpp.o: /home/dima/programm_cpp/aip-project-2-buhs/main.cpp
CMakeFiles/aip_project_2_buhs.dir/main.cpp.o: CMakeFiles/aip_project_2_buhs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/aip_project_2_buhs.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/aip_project_2_buhs.dir/main.cpp.o -MF CMakeFiles/aip_project_2_buhs.dir/main.cpp.o.d -o CMakeFiles/aip_project_2_buhs.dir/main.cpp.o -c /home/dima/programm_cpp/aip-project-2-buhs/main.cpp

CMakeFiles/aip_project_2_buhs.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/aip_project_2_buhs.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dima/programm_cpp/aip-project-2-buhs/main.cpp > CMakeFiles/aip_project_2_buhs.dir/main.cpp.i

CMakeFiles/aip_project_2_buhs.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/aip_project_2_buhs.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dima/programm_cpp/aip-project-2-buhs/main.cpp -o CMakeFiles/aip_project_2_buhs.dir/main.cpp.s

CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o: CMakeFiles/aip_project_2_buhs.dir/flags.make
CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o: /home/dima/programm_cpp/aip-project-2-buhs/neural_net.cpp
CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o: CMakeFiles/aip_project_2_buhs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o -MF CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o.d -o CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o -c /home/dima/programm_cpp/aip-project-2-buhs/neural_net.cpp

CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dima/programm_cpp/aip-project-2-buhs/neural_net.cpp > CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.i

CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dima/programm_cpp/aip-project-2-buhs/neural_net.cpp -o CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.s

CMakeFiles/aip_project_2_buhs.dir/program.cpp.o: CMakeFiles/aip_project_2_buhs.dir/flags.make
CMakeFiles/aip_project_2_buhs.dir/program.cpp.o: /home/dima/programm_cpp/aip-project-2-buhs/program.cpp
CMakeFiles/aip_project_2_buhs.dir/program.cpp.o: CMakeFiles/aip_project_2_buhs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/aip_project_2_buhs.dir/program.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/aip_project_2_buhs.dir/program.cpp.o -MF CMakeFiles/aip_project_2_buhs.dir/program.cpp.o.d -o CMakeFiles/aip_project_2_buhs.dir/program.cpp.o -c /home/dima/programm_cpp/aip-project-2-buhs/program.cpp

CMakeFiles/aip_project_2_buhs.dir/program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/aip_project_2_buhs.dir/program.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dima/programm_cpp/aip-project-2-buhs/program.cpp > CMakeFiles/aip_project_2_buhs.dir/program.cpp.i

CMakeFiles/aip_project_2_buhs.dir/program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/aip_project_2_buhs.dir/program.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dima/programm_cpp/aip-project-2-buhs/program.cpp -o CMakeFiles/aip_project_2_buhs.dir/program.cpp.s

# Object files for target aip_project_2_buhs
aip_project_2_buhs_OBJECTS = \
"CMakeFiles/aip_project_2_buhs.dir/main.cpp.o" \
"CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o" \
"CMakeFiles/aip_project_2_buhs.dir/program.cpp.o"

# External object files for target aip_project_2_buhs
aip_project_2_buhs_EXTERNAL_OBJECTS =

aip_project_2_buhs: CMakeFiles/aip_project_2_buhs.dir/main.cpp.o
aip_project_2_buhs: CMakeFiles/aip_project_2_buhs.dir/neural_net.cpp.o
aip_project_2_buhs: CMakeFiles/aip_project_2_buhs.dir/program.cpp.o
aip_project_2_buhs: CMakeFiles/aip_project_2_buhs.dir/build.make
aip_project_2_buhs: CMakeFiles/aip_project_2_buhs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable aip_project_2_buhs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aip_project_2_buhs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aip_project_2_buhs.dir/build: aip_project_2_buhs
.PHONY : CMakeFiles/aip_project_2_buhs.dir/build

CMakeFiles/aip_project_2_buhs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aip_project_2_buhs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aip_project_2_buhs.dir/clean

CMakeFiles/aip_project_2_buhs.dir/depend:
	cd /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dima/programm_cpp/aip-project-2-buhs /home/dima/programm_cpp/aip-project-2-buhs /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug /home/dima/programm_cpp/aip-project-2-buhs/cmake-build-debug/CMakeFiles/aip_project_2_buhs.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/aip_project_2_buhs.dir/depend

