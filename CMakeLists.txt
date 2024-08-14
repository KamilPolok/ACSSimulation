cmake_minimum_required(VERSION 3.20.)

set(namespace "acss")

project("ACSSimulation"
    VERSION 0.1.0
    DESCRIPTION "C++ library for simulation of the Automatic Control Systems"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------NAMING------------------------------------------------

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}")

# -----------------------------------------------OPTIONS-----------------------------------------------

option(BUILD_TESTS "Build the tests." OFF)
option(BUILD_EXAMPLES "Build the library usage examples" OFF)
option(ENABLE_ASAN "Use Clang Adress Sanitizer for detecting memory leaks" ON)

# ----------------------------------------LIBRARY CONFIGURATION----------------------------------------

# Set the postfix "d" for the resulting .so or .dll files when building the library in DEBUG mode
set(CMAKE_DEBUG_POSTFIX "d")

# Add library target
add_library(${PROJECT_NAME})

# Set properties for the target
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        VERSION ${PROJECT_VERSION} # Set the library version to the project version
        SOVERSION ${PROJECT_VERSION_MAJOR} # Set the compatibility version for the library to the major number of the version
)

target_sources(${PROJECT_NAME}
    PRIVATE
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

# Set include directories
target_include_directories(${PROJECT_NAME}
PRIVATE
    ${SRC_DIR} # Where the library itself will look for its INTERNAL headers
PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIR}> # Where top-level project will look for the library's PUBLIC headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # Where external projects will look for the library's PUBLIC headers
)

# Without it public headers won't get installed
set(public_headers
    ${INCLUDE_DIR}/ACSSimulation.hpp
    ${INCLUDE_DIR}/ActuatorIf.hpp
    ${INCLUDE_DIR}/BBController.hpp
    ${INCLUDE_DIR}/ControlObjectIf.hpp
    ${INCLUDE_DIR}/ControllerFactory.hpp
    ${INCLUDE_DIR}/ControllerIf.hpp
    ${INCLUDE_DIR}/Heater.hpp
    ${INCLUDE_DIR}/PIDController.hpp
    ${INCLUDE_DIR}/Room.hpp
    ${INCLUDE_DIR}/Simulation.hpp
)

# Where to find CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
include(Installing)

# ----------------------------------------UNIT TESTS----------------------------------------

if(BUILD_TESTS)
    message("Unit Tests enabled")
    enable_testing()
    add_subdirectory(test)
endif()

# ----------------------------------CLANG ADRESS SANITIZER----------------------------------

if(ENABLE_ASAN)
    message("Clang Adress Sanitizer enabled")
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
endif()

# -----------------------------------------EXAMPLES-----------------------------------------

if(BUILD_EXAMPLES)
    message("Building library usage examples")
    add_subdirectory(examples)
endif()
 