# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TCP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TCP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCP.dir/flags.make

CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj: CMakeFiles/TCP.dir/flags.make
CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj: CMakeFiles/TCP.dir/includes_CXX.rsp
CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj: ../TCP/stdafx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TCP.dir\TCP\stdafx.cpp.obj -c "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\stdafx.cpp"

CMakeFiles/TCP.dir/TCP/stdafx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCP.dir/TCP/stdafx.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\stdafx.cpp" > CMakeFiles\TCP.dir\TCP\stdafx.cpp.i

CMakeFiles/TCP.dir/TCP/stdafx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCP.dir/TCP/stdafx.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\stdafx.cpp" -o CMakeFiles\TCP.dir\TCP\stdafx.cpp.s

CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.requires:

.PHONY : CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.requires

CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.provides: CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.requires
	$(MAKE) -f CMakeFiles\TCP.dir\build.make CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.provides.build
.PHONY : CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.provides

CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.provides.build: CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj


CMakeFiles/TCP.dir/TCP/TCP.cpp.obj: CMakeFiles/TCP.dir/flags.make
CMakeFiles/TCP.dir/TCP/TCP.cpp.obj: CMakeFiles/TCP.dir/includes_CXX.rsp
CMakeFiles/TCP.dir/TCP/TCP.cpp.obj: ../TCP/TCP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TCP.dir/TCP/TCP.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TCP.dir\TCP\TCP.cpp.obj -c "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\TCP.cpp"

CMakeFiles/TCP.dir/TCP/TCP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCP.dir/TCP/TCP.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\TCP.cpp" > CMakeFiles\TCP.dir\TCP\TCP.cpp.i

CMakeFiles/TCP.dir/TCP/TCP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCP.dir/TCP/TCP.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\TCP\TCP.cpp" -o CMakeFiles\TCP.dir\TCP\TCP.cpp.s

CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.requires:

.PHONY : CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.requires

CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.provides: CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.requires
	$(MAKE) -f CMakeFiles\TCP.dir\build.make CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.provides.build
.PHONY : CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.provides

CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.provides.build: CMakeFiles/TCP.dir/TCP/TCP.cpp.obj


# Object files for target TCP
TCP_OBJECTS = \
"CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj" \
"CMakeFiles/TCP.dir/TCP/TCP.cpp.obj"

# External object files for target TCP
TCP_EXTERNAL_OBJECTS =

TCP.exe: CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj
TCP.exe: CMakeFiles/TCP.dir/TCP/TCP.cpp.obj
TCP.exe: CMakeFiles/TCP.dir/build.make
TCP.exe: CMakeFiles/TCP.dir/linklibs.rsp
TCP.exe: CMakeFiles/TCP.dir/objects1.rsp
TCP.exe: CMakeFiles/TCP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable TCP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TCP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCP.dir/build: TCP.exe

.PHONY : CMakeFiles/TCP.dir/build

CMakeFiles/TCP.dir/requires: CMakeFiles/TCP.dir/TCP/stdafx.cpp.obj.requires
CMakeFiles/TCP.dir/requires: CMakeFiles/TCP.dir/TCP/TCP.cpp.obj.requires

.PHONY : CMakeFiles/TCP.dir/requires

CMakeFiles/TCP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TCP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TCP.dir/clean

CMakeFiles/TCP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP" "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP" "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug" "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug" "C:\Users\arllk\Documents\Visual Studio 2017\Projects\TCP\cmake-build-debug\CMakeFiles\TCP.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TCP.dir/depend

