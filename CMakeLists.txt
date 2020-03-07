# cmake_minimum_required(VERSION <specify CMake version here>)
project(Queue_MM1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Queue_MM1 main.cpp Customer.cpp Customer.h EventScheduler.cpp EventScheduler.h)