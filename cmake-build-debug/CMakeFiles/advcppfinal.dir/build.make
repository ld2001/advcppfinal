# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\LDin21\Documents\GitHub\advcppfinal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/advcppfinal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/advcppfinal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/advcppfinal.dir/flags.make

CMakeFiles/advcppfinal.dir/bitmap.cpp.obj: CMakeFiles/advcppfinal.dir/flags.make
CMakeFiles/advcppfinal.dir/bitmap.cpp.obj: CMakeFiles/advcppfinal.dir/includes_CXX.rsp
CMakeFiles/advcppfinal.dir/bitmap.cpp.obj: ../bitmap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/advcppfinal.dir/bitmap.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\advcppfinal.dir\bitmap.cpp.obj -c C:\Users\LDin21\Documents\GitHub\advcppfinal\bitmap.cpp

CMakeFiles/advcppfinal.dir/bitmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advcppfinal.dir/bitmap.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\LDin21\Documents\GitHub\advcppfinal\bitmap.cpp > CMakeFiles\advcppfinal.dir\bitmap.cpp.i

CMakeFiles/advcppfinal.dir/bitmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advcppfinal.dir/bitmap.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\LDin21\Documents\GitHub\advcppfinal\bitmap.cpp -o CMakeFiles\advcppfinal.dir\bitmap.cpp.s

CMakeFiles/advcppfinal.dir/main.cpp.obj: CMakeFiles/advcppfinal.dir/flags.make
CMakeFiles/advcppfinal.dir/main.cpp.obj: CMakeFiles/advcppfinal.dir/includes_CXX.rsp
CMakeFiles/advcppfinal.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/advcppfinal.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\advcppfinal.dir\main.cpp.obj -c C:\Users\LDin21\Documents\GitHub\advcppfinal\main.cpp

CMakeFiles/advcppfinal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advcppfinal.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\LDin21\Documents\GitHub\advcppfinal\main.cpp > CMakeFiles\advcppfinal.dir\main.cpp.i

CMakeFiles/advcppfinal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advcppfinal.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\LDin21\Documents\GitHub\advcppfinal\main.cpp -o CMakeFiles\advcppfinal.dir\main.cpp.s

# Object files for target advcppfinal
advcppfinal_OBJECTS = \
"CMakeFiles/advcppfinal.dir/bitmap.cpp.obj" \
"CMakeFiles/advcppfinal.dir/main.cpp.obj"

# External object files for target advcppfinal
advcppfinal_EXTERNAL_OBJECTS =

advcppfinal.exe: CMakeFiles/advcppfinal.dir/bitmap.cpp.obj
advcppfinal.exe: CMakeFiles/advcppfinal.dir/main.cpp.obj
advcppfinal.exe: CMakeFiles/advcppfinal.dir/build.make
advcppfinal.exe: CMakeFiles/advcppfinal.dir/linklibs.rsp
advcppfinal.exe: CMakeFiles/advcppfinal.dir/objects1.rsp
advcppfinal.exe: CMakeFiles/advcppfinal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable advcppfinal.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\advcppfinal.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/advcppfinal.dir/build: advcppfinal.exe

.PHONY : CMakeFiles/advcppfinal.dir/build

CMakeFiles/advcppfinal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\advcppfinal.dir\cmake_clean.cmake
.PHONY : CMakeFiles/advcppfinal.dir/clean

CMakeFiles/advcppfinal.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\LDin21\Documents\GitHub\advcppfinal C:\Users\LDin21\Documents\GitHub\advcppfinal C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug C:\Users\LDin21\Documents\GitHub\advcppfinal\cmake-build-debug\CMakeFiles\advcppfinal.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/advcppfinal.dir/depend

