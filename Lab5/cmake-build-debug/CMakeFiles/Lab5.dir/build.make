# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lab5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab5.dir/flags.make

CMakeFiles/Lab5.dir/lc3bsim5.c.o: CMakeFiles/Lab5.dir/flags.make
CMakeFiles/Lab5.dir/lc3bsim5.c.o: ../lc3bsim5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab5.dir/lc3bsim5.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Lab5.dir/lc3bsim5.c.o   -c "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/lc3bsim5.c"

CMakeFiles/Lab5.dir/lc3bsim5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lab5.dir/lc3bsim5.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/lc3bsim5.c" > CMakeFiles/Lab5.dir/lc3bsim5.c.i

CMakeFiles/Lab5.dir/lc3bsim5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lab5.dir/lc3bsim5.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/lc3bsim5.c" -o CMakeFiles/Lab5.dir/lc3bsim5.c.s

# Object files for target Lab5
Lab5_OBJECTS = \
"CMakeFiles/Lab5.dir/lc3bsim5.c.o"

# External object files for target Lab5
Lab5_EXTERNAL_OBJECTS =

Lab5: CMakeFiles/Lab5.dir/lc3bsim5.c.o
Lab5: CMakeFiles/Lab5.dir/build.make
Lab5: CMakeFiles/Lab5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Lab5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab5.dir/build: Lab5

.PHONY : CMakeFiles/Lab5.dir/build

CMakeFiles/Lab5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab5.dir/clean

CMakeFiles/Lab5.dir/depend:
	cd "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5" "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5" "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug" "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug" "/Users/dhruvsandesara/Desktop/sem5/ee460n ComArch/Labs/Lab5/cmake-build-debug/CMakeFiles/Lab5.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab5.dir/depend
