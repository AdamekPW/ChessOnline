# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/adam/Pulpit/ChessServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adam/Pulpit/ChessServer/build

# Include any dependencies generated for this target.
include Client/CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Client/CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include Client/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include Client/CMakeFiles/client.dir/flags.make

Client/CMakeFiles/client.dir/src/Client.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/src/Client.cpp.o: ../Client/src/Client.cpp
Client/CMakeFiles/client.dir/src/Client.cpp.o: Client/CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adam/Pulpit/ChessServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Client/CMakeFiles/client.dir/src/Client.cpp.o"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Client/CMakeFiles/client.dir/src/Client.cpp.o -MF CMakeFiles/client.dir/src/Client.cpp.o.d -o CMakeFiles/client.dir/src/Client.cpp.o -c /home/adam/Pulpit/ChessServer/Client/src/Client.cpp

Client/CMakeFiles/client.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/Client.cpp.i"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Pulpit/ChessServer/Client/src/Client.cpp > CMakeFiles/client.dir/src/Client.cpp.i

Client/CMakeFiles/client.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/Client.cpp.s"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Pulpit/ChessServer/Client/src/Client.cpp -o CMakeFiles/client.dir/src/Client.cpp.s

Client/CMakeFiles/client.dir/src/main.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/src/main.cpp.o: ../Client/src/main.cpp
Client/CMakeFiles/client.dir/src/main.cpp.o: Client/CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adam/Pulpit/ChessServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Client/CMakeFiles/client.dir/src/main.cpp.o"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Client/CMakeFiles/client.dir/src/main.cpp.o -MF CMakeFiles/client.dir/src/main.cpp.o.d -o CMakeFiles/client.dir/src/main.cpp.o -c /home/adam/Pulpit/ChessServer/Client/src/main.cpp

Client/CMakeFiles/client.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/main.cpp.i"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/Pulpit/ChessServer/Client/src/main.cpp > CMakeFiles/client.dir/src/main.cpp.i

Client/CMakeFiles/client.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/main.cpp.s"
	cd /home/adam/Pulpit/ChessServer/build/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/Pulpit/ChessServer/Client/src/main.cpp -o CMakeFiles/client.dir/src/main.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/Client.cpp.o" \
"CMakeFiles/client.dir/src/main.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

Client/client: Client/CMakeFiles/client.dir/src/Client.cpp.o
Client/client: Client/CMakeFiles/client.dir/src/main.cpp.o
Client/client: Client/CMakeFiles/client.dir/build.make
Client/client: Shared/libshared_lib.a
Client/client: Client/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adam/Pulpit/ChessServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable client"
	cd /home/adam/Pulpit/ChessServer/build/Client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Client/CMakeFiles/client.dir/build: Client/client
.PHONY : Client/CMakeFiles/client.dir/build

Client/CMakeFiles/client.dir/clean:
	cd /home/adam/Pulpit/ChessServer/build/Client && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : Client/CMakeFiles/client.dir/clean

Client/CMakeFiles/client.dir/depend:
	cd /home/adam/Pulpit/ChessServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adam/Pulpit/ChessServer /home/adam/Pulpit/ChessServer/Client /home/adam/Pulpit/ChessServer/build /home/adam/Pulpit/ChessServer/build/Client /home/adam/Pulpit/ChessServer/build/Client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Client/CMakeFiles/client.dir/depend
