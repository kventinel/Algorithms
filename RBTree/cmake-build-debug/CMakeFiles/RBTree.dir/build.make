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
CMAKE_SOURCE_DIR = /home/alex/Documents/Git/Algorithms/RBTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RBTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RBTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RBTree.dir/flags.make

CMakeFiles/RBTree.dir/main.cpp.o: CMakeFiles/RBTree.dir/flags.make
CMakeFiles/RBTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RBTree.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RBTree.dir/main.cpp.o -c /home/alex/Documents/Git/Algorithms/RBTree/main.cpp

CMakeFiles/RBTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RBTree.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Documents/Git/Algorithms/RBTree/main.cpp > CMakeFiles/RBTree.dir/main.cpp.i

CMakeFiles/RBTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RBTree.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Documents/Git/Algorithms/RBTree/main.cpp -o CMakeFiles/RBTree.dir/main.cpp.s

CMakeFiles/RBTree.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/RBTree.dir/main.cpp.o.requires

CMakeFiles/RBTree.dir/main.cpp.o.provides: CMakeFiles/RBTree.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/RBTree.dir/build.make CMakeFiles/RBTree.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/RBTree.dir/main.cpp.o.provides

CMakeFiles/RBTree.dir/main.cpp.o.provides.build: CMakeFiles/RBTree.dir/main.cpp.o


# Object files for target RBTree
RBTree_OBJECTS = \
"CMakeFiles/RBTree.dir/main.cpp.o"

# External object files for target RBTree
RBTree_EXTERNAL_OBJECTS =

RBTree: CMakeFiles/RBTree.dir/main.cpp.o
RBTree: CMakeFiles/RBTree.dir/build.make
RBTree: CMakeFiles/RBTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RBTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RBTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RBTree.dir/build: RBTree

.PHONY : CMakeFiles/RBTree.dir/build

CMakeFiles/RBTree.dir/requires: CMakeFiles/RBTree.dir/main.cpp.o.requires

.PHONY : CMakeFiles/RBTree.dir/requires

CMakeFiles/RBTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RBTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RBTree.dir/clean

CMakeFiles/RBTree.dir/depend:
	cd /home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Documents/Git/Algorithms/RBTree /home/alex/Documents/Git/Algorithms/RBTree /home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug /home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug /home/alex/Documents/Git/Algorithms/RBTree/cmake-build-debug/CMakeFiles/RBTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RBTree.dir/depend

