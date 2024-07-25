cmake_minimum_required(VERSION 3.16)

project(Simulation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--------------------------NAMING---------------------------
set(EXE_NAME ${PROJECT_NAME})
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/inc")

#--------------------------OPTIONS--------------------------
option(BUILD_TESTS "Build the tests." OFF)
option(ENABLE_ASAN "Use Clang Adress Sanitizer for detecting memory leaks" ON)

#-----------------------CONFIGURATION-----------------------
add_executable(${EXE_NAME} main.cpp
    ${SRC_DIR}/ActuatorIf.cpp
    ${SRC_DIR}/ControlObjectIf.cpp
    ${SRC_DIR}/Heater.cpp
    ${SRC_DIR}/Room.cpp
    ${SRC_DIR}/ControllerFactory.cpp
    ${SRC_DIR}/ControllerIf.cpp
    ${SRC_DIR}/BBController.cpp
    ${SRC_DIR}/PIDController.cpp
    ${SRC_DIR}/Simulation.cpp
    )

target_include_directories(${EXE_NAME} PRIVATE ${INC_DIR})

if(BUILD_TESTS)
    message("Unit Tests enabled")
    enable_testing()
    add_subdirectory(tst)
endif()

if(ENABLE_ASAN)
    message("Clang Adress Sanitizer enabled")
    target_compile_options(${EXE_NAME} PUBLIC -fsanitize=address)
    target_link_options(${EXE_NAME} PUBLIC -fsanitize=address)
endif()
