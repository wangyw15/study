# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Projects/study-github/sort_show

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Projects/study-github/sort_show/build

# Include any dependencies generated for this target.
include CMakeFiles/libvisualizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libvisualizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libvisualizer.dir/flags.make

CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o: CMakeFiles/libvisualizer.dir/flags.make
CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o: ../src/visualizer/visualizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Projects/study-github/sort_show/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o -c /mnt/d/Projects/study-github/sort_show/src/visualizer/visualizer.cpp

CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Projects/study-github/sort_show/src/visualizer/visualizer.cpp > CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.i

CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Projects/study-github/sort_show/src/visualizer/visualizer.cpp -o CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.s

# Object files for target libvisualizer
libvisualizer_OBJECTS = \
"CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o"

# External object files for target libvisualizer
libvisualizer_EXTERNAL_OBJECTS =

lib/liblibvisualizer.a: CMakeFiles/libvisualizer.dir/src/visualizer/visualizer.cpp.o
lib/liblibvisualizer.a: CMakeFiles/libvisualizer.dir/build.make
lib/liblibvisualizer.a: CMakeFiles/libvisualizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Projects/study-github/sort_show/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library lib/liblibvisualizer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/libvisualizer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libvisualizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libvisualizer.dir/build: lib/liblibvisualizer.a

.PHONY : CMakeFiles/libvisualizer.dir/build

CMakeFiles/libvisualizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libvisualizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libvisualizer.dir/clean

CMakeFiles/libvisualizer.dir/depend:
	cd /mnt/d/Projects/study-github/sort_show/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Projects/study-github/sort_show /mnt/d/Projects/study-github/sort_show /mnt/d/Projects/study-github/sort_show/build /mnt/d/Projects/study-github/sort_show/build /mnt/d/Projects/study-github/sort_show/build/CMakeFiles/libvisualizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libvisualizer.dir/depend

