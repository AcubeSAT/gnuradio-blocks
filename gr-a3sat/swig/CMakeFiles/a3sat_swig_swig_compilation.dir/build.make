# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/164/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/164/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat

# Utility rule file for a3sat_swig_swig_compilation.

# Include any custom commands dependencies for this target.
include swig/CMakeFiles/a3sat_swig_swig_compilation.dir/compiler_depend.make

# Include the progress variables for this target.
include swig/CMakeFiles/a3sat_swig_swig_compilation.dir/progress.make

swig/CMakeFiles/a3sat_swig_swig_compilation: swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp

swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp: /usr/lib/python3/dist-packages/gnuradio/gr/_runtime_swig.so
swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp: swig/a3sat_swig.i
swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp: swig/a3sat_swig.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source a3sat_swig.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig && /snap/clion/164/bin/cmake/linux/bin/cmake -E make_directory /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig/CMakeFiles/a3sat_swig.dir
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig && /snap/clion/164/bin/cmake/linux/bin/cmake -E touch /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig && /snap/clion/164/bin/cmake/linux/bin/cmake -E env SWIG_LIB=/usr/share/swig4.0 /usr/bin/swig4.0 -python -fvirtual -keyword -w511 -w314 -relativeimport -py3 -module a3sat_swig -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig -I/usr/include/gnuradio/swig -I/usr/include/python3.8 -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/local/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/../include -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig -I/usr/include/gnuradio/swig -I/usr/include/python3.8 -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/local/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/../include -outdir /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig -c++ -o /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON_wrap.cxx /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig/a3sat_swig.i

a3sat_swig_swig_compilation: swig/CMakeFiles/a3sat_swig.dir/a3sat_swigPYTHON.stamp
a3sat_swig_swig_compilation: swig/CMakeFiles/a3sat_swig_swig_compilation
a3sat_swig_swig_compilation: swig/CMakeFiles/a3sat_swig_swig_compilation.dir/build.make
.PHONY : a3sat_swig_swig_compilation

# Rule to build all files generated by this target.
swig/CMakeFiles/a3sat_swig_swig_compilation.dir/build: a3sat_swig_swig_compilation
.PHONY : swig/CMakeFiles/a3sat_swig_swig_compilation.dir/build

swig/CMakeFiles/a3sat_swig_swig_compilation.dir/clean:
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig && $(CMAKE_COMMAND) -P CMakeFiles/a3sat_swig_swig_compilation.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/a3sat_swig_swig_compilation.dir/clean

swig/CMakeFiles/a3sat_swig_swig_compilation.dir/depend:
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/swig/CMakeFiles/a3sat_swig_swig_compilation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/a3sat_swig_swig_compilation.dir/depend

