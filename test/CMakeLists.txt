cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/src)

enable_testing()
find_package(GTest REQUIRED)

set(
    LIBS 
    Elevator
    Simulation
)

add_executable(gtest gtest.cc)
target_link_libraries(gtest GTest::GTest GTest::Main ${LIBS})

add_test(ElevatorControlSystem gtest)
