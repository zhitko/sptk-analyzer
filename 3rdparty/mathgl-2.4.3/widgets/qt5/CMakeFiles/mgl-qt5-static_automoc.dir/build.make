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

# Utility rule file for mgl-qt5-static_automoc.

# Include the progress variables for this target.
include widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/progress.make

widgets/qt5/CMakeFiles/mgl-qt5-static_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc and uic for target mgl-qt5-static"
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5 && /usr/bin/cmake -E cmake_autogen /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/ Release

mgl-qt5-static_automoc: widgets/qt5/CMakeFiles/mgl-qt5-static_automoc
mgl-qt5-static_automoc: widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/build.make

.PHONY : mgl-qt5-static_automoc

# Rule to build all files generated by this target.
widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/build: mgl-qt5-static_automoc

.PHONY : widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/build

widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/clean:
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5 && $(CMAKE_COMMAND) -P CMakeFiles/mgl-qt5-static_automoc.dir/cmake_clean.cmake
.PHONY : widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/clean

widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/depend:
	cd /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5 /home/vzhitko/Dev/UIIP/inton-trainer/3rdparty/mathgl-2.4.3/widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : widgets/qt5/CMakeFiles/mgl-qt5-static_automoc.dir/depend

