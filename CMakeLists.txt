cmake_minimum_required(VERSION 3.2)
project(AIHW4_Q_Learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES main.cpp)
add_executable(AIHW4_Q_Learning ${SOURCE_FILES} AIHW4_Environment.cpp AIHW4_Environment.h AIHW4_burglar.cpp AIHW4_burglar.h)