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
include CMakeFiles/libutil.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libutil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libutil.dir/flags.make

CMakeFiles/libutil.dir/src/util/util.cpp.o: CMakeFiles/libutil.dir/flags.make
CMakeFiles/libutil.dir/src/util/util.cpp.o: ../src/util/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Projects/study-github/sort_show/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libutil.dir/src/util/util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libutil.dir/src/util/util.cpp.o -c /mnt/d/Projects/study-github/sort_show/src/util/util.cpp

CMakeFiles/libutil.dir/src/util/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libutil.dir/src/util/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Projects/study-github/sort_show/src/util/util.cpp > CMakeFiles/libutil.dir/src/util/util.cpp.i

CMakeFiles/libutil.dir/src/util/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libutil.dir/src/util/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Projects/study-github/sort_show/src/util/util.cpp -o CMakeFiles/libutil.dir/src/util/util.cpp.s

# Object files for target libutil
libutil_OBJECTS = \
"CMakeFiles/libutil.dir/src/util/util.cpp.o"

# External object files for target libutil
libutil_EXTERNAL_OBJECTS =

lib/liblibutil.a: CMakeFiles/libutil.dir/src/util/util.cpp.o
lib/liblibutil.a: CMakeFiles/libutil.dir/build.make
lib/liblibutil.a: CMakeFiles/libutil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Projects/study-github/sort_show/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library lib/liblibutil.a"
	$(CMAKE_COMMAND) -P CMakeFiles/libutil.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libutil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libutil.dir/build: lib/liblibutil.a

.PHONY : CMakeFiles/libutil.dir/build

CMakeFiles/libutil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libutil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libutil.dir/clean

CMakeFiles/libutil.dir/depend:
	cd /mnt/d/Projects/study-github/sort_show/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Projects/study-github/sort_show /mnt/d/Projects/study-github/sort_show /mnt/d/Projects/study-github/sort_show/build /mnt/d/Projects/study-github/sort_show/build /mnt/d/Projects/study-github/sort_show/build/CMakeFiles/libutil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libutil.dir/depend

