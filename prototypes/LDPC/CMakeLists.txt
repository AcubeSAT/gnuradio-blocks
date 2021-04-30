cmake_minimum_required(VERSION 3.17)
project(Desktop)

set(CMAKE_CXX_STANDARD 14)

include_directories(../../gr-a3sat/include)
include_directories(../../gr-a3sat/include/a3sat)
include_directories(../../gr-a3sat/lib)

add_executable(Desktop
        ldpc_encoder.cpp
        ldpc_decoder.cpp
        ldpc_check_decoder.cpp)
