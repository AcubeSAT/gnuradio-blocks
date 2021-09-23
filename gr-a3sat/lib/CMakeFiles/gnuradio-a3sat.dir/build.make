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

# Include any dependencies generated for this target.
include lib/CMakeFiles/gnuradio-a3sat.dir/depend.make
# Include the progress variables for this target.
include lib/CMakeFiles/gnuradio-a3sat.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/gnuradio-a3sat.dir/flags.make

lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o: lib/conv_enc_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_enc_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_enc_impl.cc > CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_enc_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.s

lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o: lib/conv_dec_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_dec_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_dec_impl.cc > CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/conv_dec_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.s

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o: lib/ldpc_enc_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_enc_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_enc_impl.cc > CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_enc_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.s

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o: lib/ldpc_dec_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_dec_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_dec_impl.cc > CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/ldpc_dec_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.s

lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o: lib/bch_enc_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_enc_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_enc_impl.cc > CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_enc_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.s

lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o: lib/CMakeFiles/gnuradio-a3sat.dir/flags.make
lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o: lib/bch_dec_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o -c /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_dec_impl.cc

lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.i"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_dec_impl.cc > CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.i

lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.s"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/bch_dec_impl.cc -o CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.s

# Object files for target gnuradio-a3sat
gnuradio__a3sat_OBJECTS = \
"CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o" \
"CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o" \
"CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o" \
"CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o" \
"CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o" \
"CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o"

# External object files for target gnuradio-a3sat
gnuradio__a3sat_EXTERNAL_OBJECTS =

lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/conv_enc_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/conv_dec_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_enc_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/ldpc_dec_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/bch_enc_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/bch_dec_impl.cc.o
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/build.make
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libgnuradio-runtime.so.3.8.3.1
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libthrift.so
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libgnuradio-pmt.so.3.8.3.1
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/local/lib/libvolk.so.2.5.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/liblog4cpp.so
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libgmpxx.so
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: /usr/lib/x86_64-linux-gnu/libgmp.so
lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown: lib/CMakeFiles/gnuradio-a3sat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library libgnuradio-a3sat.so"
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gnuradio-a3sat.dir/link.txt --verbose=$(VERBOSE)
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown libgnuradio-a3sat.so.1.0.0git libgnuradio-a3sat.so

lib/libgnuradio-a3sat.so.1.0.0git: lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libgnuradio-a3sat.so.1.0.0git

lib/libgnuradio-a3sat.so: lib/libgnuradio-a3sat.so.v1.0-compat-xxx-xunknown
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libgnuradio-a3sat.so

# Rule to build all files generated by this target.
lib/CMakeFiles/gnuradio-a3sat.dir/build: lib/libgnuradio-a3sat.so
.PHONY : lib/CMakeFiles/gnuradio-a3sat.dir/build

lib/CMakeFiles/gnuradio-a3sat.dir/clean:
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib && $(CMAKE_COMMAND) -P CMakeFiles/gnuradio-a3sat.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/gnuradio-a3sat.dir/clean

lib/CMakeFiles/gnuradio-a3sat.dir/depend:
	cd /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib /home/efthamar/CLionProjects/error-correction-codes/gr-a3sat/lib/CMakeFiles/gnuradio-a3sat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/gnuradio-a3sat.dir/depend
