# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/baotran/Desktop/Data Structure/p2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/p2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p2.dir/flags.make

CMakeFiles/p2.dir/p2.cpp.o: CMakeFiles/p2.dir/flags.make
CMakeFiles/p2.dir/p2.cpp.o: ../p2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p2.dir/p2.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p2.dir/p2.cpp.o -c "/Users/baotran/Desktop/Data Structure/p2/p2.cpp"

CMakeFiles/p2.dir/p2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p2.dir/p2.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/baotran/Desktop/Data Structure/p2/p2.cpp" > CMakeFiles/p2.dir/p2.cpp.i

CMakeFiles/p2.dir/p2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p2.dir/p2.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/baotran/Desktop/Data Structure/p2/p2.cpp" -o CMakeFiles/p2.dir/p2.cpp.s

# Object files for target p2
p2_OBJECTS = \
"CMakeFiles/p2.dir/p2.cpp.o"

# External object files for target p2
p2_EXTERNAL_OBJECTS =

p2: CMakeFiles/p2.dir/p2.cpp.o
p2: CMakeFiles/p2.dir/build.make
p2: CMakeFiles/p2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p2.dir/build: p2

.PHONY : CMakeFiles/p2.dir/build

CMakeFiles/p2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p2.dir/clean

CMakeFiles/p2.dir/depend:
	cd "/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/baotran/Desktop/Data Structure/p2" "/Users/baotran/Desktop/Data Structure/p2" "/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug" "/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug" "/Users/baotran/Desktop/Data Structure/p2/cmake-build-debug/CMakeFiles/p2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/p2.dir/depend

