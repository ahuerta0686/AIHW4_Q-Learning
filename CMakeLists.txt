cmake_minimum_required(VERSION 3.2)
project(AIHW4_Q_Learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AIHW4_Q_Learning ${SOURCE_FILES})