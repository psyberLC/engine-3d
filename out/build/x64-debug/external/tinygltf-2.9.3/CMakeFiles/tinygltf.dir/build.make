# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sesa768246\to_github\engine-3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug

# Include any dependencies generated for this target.
include external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/compiler_depend.make

# Include the progress variables for this target.
include external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/progress.make

# Include the compile flags for this target's objects.
include external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/flags.make

external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj: external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/flags.make
external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj: C:/Users/sesa768246/to_github/engine-3d/external/tinygltf-2.9.3/tiny_gltf.cc
external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj: external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj"
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj -MF CMakeFiles\tinygltf.dir\tiny_gltf.cc.obj.d -o CMakeFiles\tinygltf.dir\tiny_gltf.cc.obj -c C:\Users\sesa768246\to_github\engine-3d\external\tinygltf-2.9.3\tiny_gltf.cc

external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tinygltf.dir/tiny_gltf.cc.i"
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sesa768246\to_github\engine-3d\external\tinygltf-2.9.3\tiny_gltf.cc > CMakeFiles\tinygltf.dir\tiny_gltf.cc.i

external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tinygltf.dir/tiny_gltf.cc.s"
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sesa768246\to_github\engine-3d\external\tinygltf-2.9.3\tiny_gltf.cc -o CMakeFiles\tinygltf.dir\tiny_gltf.cc.s

# Object files for target tinygltf
tinygltf_OBJECTS = \
"CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj"

# External object files for target tinygltf
tinygltf_EXTERNAL_OBJECTS =

external/tinygltf-2.9.3/libtinygltf.a: external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/tiny_gltf.cc.obj
external/tinygltf-2.9.3/libtinygltf.a: external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/build.make
external/tinygltf-2.9.3/libtinygltf.a: external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtinygltf.a"
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && $(CMAKE_COMMAND) -P CMakeFiles\tinygltf.dir\cmake_clean_target.cmake
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tinygltf.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/build: external/tinygltf-2.9.3/libtinygltf.a
.PHONY : external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/build

external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/clean:
	cd /d C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 && $(CMAKE_COMMAND) -P CMakeFiles\tinygltf.dir\cmake_clean.cmake
.PHONY : external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/clean

external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sesa768246\to_github\engine-3d C:\Users\sesa768246\to_github\engine-3d\external\tinygltf-2.9.3 C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3 C:\Users\sesa768246\to_github\engine-3d\out\build\x64-debug\external\tinygltf-2.9.3\CMakeFiles\tinygltf.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/tinygltf-2.9.3/CMakeFiles/tinygltf.dir/depend
