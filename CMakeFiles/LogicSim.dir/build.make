# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/beacrox/LogicSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beacrox/LogicSim

# Include any dependencies generated for this target.
include CMakeFiles/LogicSim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LogicSim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LogicSim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LogicSim.dir/flags.make

CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o: CMakeFiles/LogicSim.dir/flags.make
CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o: LogicSim_autogen/mocs_compilation.cpp
CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o: CMakeFiles/LogicSim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beacrox/LogicSim/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o -MF CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o -c /home/beacrox/LogicSim/LogicSim_autogen/mocs_compilation.cpp

CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beacrox/LogicSim/LogicSim_autogen/mocs_compilation.cpp > CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.i

CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beacrox/LogicSim/LogicSim_autogen/mocs_compilation.cpp -o CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.s

CMakeFiles/LogicSim.dir/src/main.cpp.o: CMakeFiles/LogicSim.dir/flags.make
CMakeFiles/LogicSim.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/LogicSim.dir/src/main.cpp.o: CMakeFiles/LogicSim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beacrox/LogicSim/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LogicSim.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LogicSim.dir/src/main.cpp.o -MF CMakeFiles/LogicSim.dir/src/main.cpp.o.d -o CMakeFiles/LogicSim.dir/src/main.cpp.o -c /home/beacrox/LogicSim/src/main.cpp

CMakeFiles/LogicSim.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogicSim.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beacrox/LogicSim/src/main.cpp > CMakeFiles/LogicSim.dir/src/main.cpp.i

CMakeFiles/LogicSim.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogicSim.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beacrox/LogicSim/src/main.cpp -o CMakeFiles/LogicSim.dir/src/main.cpp.s

# Object files for target LogicSim
LogicSim_OBJECTS = \
"CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/LogicSim.dir/src/main.cpp.o"

# External object files for target LogicSim
LogicSim_EXTERNAL_OBJECTS =

LogicSim: CMakeFiles/LogicSim.dir/LogicSim_autogen/mocs_compilation.cpp.o
LogicSim: CMakeFiles/LogicSim.dir/src/main.cpp.o
LogicSim: CMakeFiles/LogicSim.dir/build.make
LogicSim: /usr/lib/libQt6Widgets.so.6.4.1
LogicSim: /usr/lib/libQt6Gui.so.6.4.1
LogicSim: /usr/lib/libQt6Core.so.6.4.1
LogicSim: /usr/lib/libGLX.so
LogicSim: /usr/lib/libOpenGL.so
LogicSim: CMakeFiles/LogicSim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beacrox/LogicSim/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable LogicSim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LogicSim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LogicSim.dir/build: LogicSim
.PHONY : CMakeFiles/LogicSim.dir/build

CMakeFiles/LogicSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LogicSim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LogicSim.dir/clean

CMakeFiles/LogicSim.dir/depend:
	cd /home/beacrox/LogicSim && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beacrox/LogicSim /home/beacrox/LogicSim /home/beacrox/LogicSim /home/beacrox/LogicSim /home/beacrox/LogicSim/CMakeFiles/LogicSim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LogicSim.dir/depend

