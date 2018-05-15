cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_BINARY_DIR}/src)

add_library(Elevator Elevator.cc)
add_library(Simulation Simulation.cc)

set(SOURCE_FILES main.cc Elevator.cc Simulation.cc)
add_executable(ElevatorControlSystem ${SOURCE_FILES})