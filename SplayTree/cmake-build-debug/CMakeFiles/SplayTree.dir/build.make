# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/clion-2016.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2016.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alex/Documents/Git/Algorithms/SplayTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SplayTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SplayTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SplayTree.dir/flags.make

CMakeFiles/SplayTree.dir/main.cpp.o: CMakeFiles/SplayTree.dir/flags.make
CMakeFiles/SplayTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SplayTree.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SplayTree.dir/main.cpp.o -c /home/alex/Documents/Git/Algorithms/SplayTree/main.cpp

CMakeFiles/SplayTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SplayTree.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Documents/Git/Algorithms/SplayTree/main.cpp > CMakeFiles/SplayTree.dir/main.cpp.i

CMakeFiles/SplayTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SplayTree.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Documents/Git/Algorithms/SplayTree/main.cpp -o CMakeFiles/SplayTree.dir/main.cpp.s

CMakeFiles/SplayTree.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/SplayTree.dir/main.cpp.o.requires

CMakeFiles/SplayTree.dir/main.cpp.o.provides: CMakeFiles/SplayTree.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SplayTree.dir/build.make CMakeFiles/SplayTree.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/SplayTree.dir/main.cpp.o.provides

CMakeFiles/SplayTree.dir/main.cpp.o.provides.build: CMakeFiles/SplayTree.dir/main.cpp.o


# Object files for target SplayTree
SplayTree_OBJECTS = \
"CMakeFiles/SplayTree.dir/main.cpp.o"

# External object files for target SplayTree
SplayTree_EXTERNAL_OBJECTS =

SplayTree: CMakeFiles/SplayTree.dir/main.cpp.o
SplayTree: CMakeFiles/SplayTree.dir/build.make
SplayTree: CMakeFiles/SplayTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SplayTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SplayTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SplayTree.dir/build: SplayTree

.PHONY : CMakeFiles/SplayTree.dir/build

CMakeFiles/SplayTree.dir/requires: CMakeFiles/SplayTree.dir/main.cpp.o.requires

.PHONY : CMakeFiles/SplayTree.dir/requires

CMakeFiles/SplayTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SplayTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SplayTree.dir/clean

CMakeFiles/SplayTree.dir/depend:
	cd /home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Documents/Git/Algorithms/SplayTree /home/alex/Documents/Git/Algorithms/SplayTree /home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug /home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug /home/alex/Documents/Git/Algorithms/SplayTree/cmake-build-debug/CMakeFiles/SplayTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SplayTree.dir/depend

