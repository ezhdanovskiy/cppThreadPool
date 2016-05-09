cmake_minimum_required(VERSION 3.5)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -D_GLIBCXX_USE_NANOSLEEP -pthread")

set(SOURCE_FILES main.cpp)
add_executable(ThreadPool ${SOURCE_FILES})