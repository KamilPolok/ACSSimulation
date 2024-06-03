cmake_minimum_required(VERSION 3.16)

project(Simulation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the tests." OFF)

set(EXE_NAME ${PROJECT_NAME})
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/inc")

add_executable(${EXE_NAME} main.cpp
    ${SRC_DIR}/Room.cpp
    ${SRC_DIR}/Heater.cpp
    ${SRC_DIR}/Simulation.cpp
    ${SRC_DIR}/BBController.cpp
    ${SRC_DIR}/PIDController.cpp
    )

target_include_directories(${EXE_NAME} PRIVATE ${INC_DIR})

if(BUILD_TESTS)
    enable_testing()
add_subdirectory(tst)
endif()
