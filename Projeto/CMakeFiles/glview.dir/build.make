# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /nfs/home/lucas02/Downloads/Cg/glview-model

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nfs/home/lucas02/Downloads/Cg/glview-model

# Include any dependencies generated for this target.
include CMakeFiles/glview.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glview.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glview.dir/flags.make

CMakeFiles/glview.dir/Sources/main.cpp.o: CMakeFiles/glview.dir/flags.make
CMakeFiles/glview.dir/Sources/main.cpp.o: Sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/home/lucas02/Downloads/Cg/glview-model/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/glview.dir/Sources/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glview.dir/Sources/main.cpp.o -c /nfs/home/lucas02/Downloads/Cg/glview-model/Sources/main.cpp

CMakeFiles/glview.dir/Sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glview.dir/Sources/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /nfs/home/lucas02/Downloads/Cg/glview-model/Sources/main.cpp > CMakeFiles/glview.dir/Sources/main.cpp.i

CMakeFiles/glview.dir/Sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glview.dir/Sources/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /nfs/home/lucas02/Downloads/Cg/glview-model/Sources/main.cpp -o CMakeFiles/glview.dir/Sources/main.cpp.s

# Object files for target glview
glview_OBJECTS = \
"CMakeFiles/glview.dir/Sources/main.cpp.o"

# External object files for target glview
glview_EXTERNAL_OBJECTS =

glview: CMakeFiles/glview.dir/Sources/main.cpp.o
glview: CMakeFiles/glview.dir/build.make
glview: /usr/lib/x86_64-linux-gnu/libOpenGL.so
glview: /usr/lib/x86_64-linux-gnu/libGLX.so
glview: /usr/lib/x86_64-linux-gnu/libGLU.so
glview: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
glview: /usr/lib/x86_64-linux-gnu/libGLEW.so
glview: CMakeFiles/glview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/nfs/home/lucas02/Downloads/Cg/glview-model/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable glview"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glview.dir/build: glview

.PHONY : CMakeFiles/glview.dir/build

CMakeFiles/glview.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glview.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glview.dir/clean

CMakeFiles/glview.dir/depend:
	cd /nfs/home/lucas02/Downloads/Cg/glview-model && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/home/lucas02/Downloads/Cg/glview-model /nfs/home/lucas02/Downloads/Cg/glview-model /nfs/home/lucas02/Downloads/Cg/glview-model /nfs/home/lucas02/Downloads/Cg/glview-model /nfs/home/lucas02/Downloads/Cg/glview-model/CMakeFiles/glview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glview.dir/depend
