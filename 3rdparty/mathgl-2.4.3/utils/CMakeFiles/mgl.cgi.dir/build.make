# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3

# Include any dependencies generated for this target.
include utils/CMakeFiles/mgl.cgi.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/mgl.cgi.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/mgl.cgi.dir/flags.make

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o: utils/CMakeFiles/mgl.cgi.dir/flags.make
utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o: utils/mglcgi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o"
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o -c /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils/mglcgi.cpp

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mgl.cgi.dir/mglcgi.cpp.i"
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils/mglcgi.cpp > CMakeFiles/mgl.cgi.dir/mglcgi.cpp.i

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mgl.cgi.dir/mglcgi.cpp.s"
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils/mglcgi.cpp -o CMakeFiles/mgl.cgi.dir/mglcgi.cpp.s

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.requires:

.PHONY : utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.requires

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.provides: utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/mgl.cgi.dir/build.make utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.provides.build
.PHONY : utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.provides

utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.provides.build: utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o


# Object files for target mgl.cgi
mgl_cgi_OBJECTS = \
"CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o"

# External object files for target mgl.cgi
mgl_cgi_EXTERNAL_OBJECTS =

utils/mgl.cgi: utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o
utils/mgl.cgi: utils/CMakeFiles/mgl.cgi.dir/build.make
utils/mgl.cgi: src/libmgl.a
utils/mgl.cgi: /usr/lib/x86_64-linux-gnu/libGLU.so
utils/mgl.cgi: /usr/lib/x86_64-linux-gnu/libGL.so
utils/mgl.cgi: /usr/lib/x86_64-linux-gnu/libpng.so
utils/mgl.cgi: /usr/lib/x86_64-linux-gnu/libz.so
utils/mgl.cgi: utils/CMakeFiles/mgl.cgi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mgl.cgi"
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mgl.cgi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/mgl.cgi.dir/build: utils/mgl.cgi

.PHONY : utils/CMakeFiles/mgl.cgi.dir/build

utils/CMakeFiles/mgl.cgi.dir/requires: utils/CMakeFiles/mgl.cgi.dir/mglcgi.cpp.o.requires

.PHONY : utils/CMakeFiles/mgl.cgi.dir/requires

utils/CMakeFiles/mgl.cgi.dir/clean:
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils && $(CMAKE_COMMAND) -P CMakeFiles/mgl.cgi.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/mgl.cgi.dir/clean

utils/CMakeFiles/mgl.cgi.dir/depend:
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/utils/CMakeFiles/mgl.cgi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/mgl.cgi.dir/depend

