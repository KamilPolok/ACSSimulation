include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Define a variable for the test executable's name
set(TESTS_NAME "${EXE_NAME}_tests")

# Add test files
add_executable(${TESTS_NAME}
    ./RoomTest.cpp
    ./HeaterTest.cpp
    ./BBControllerTest.cpp
    ./PIDControllerTest.cpp
    ${SRC_DIR}/Room.cpp
    ${SRC_DIR}/Heater.cpp
    ${SRC_DIR}/ControllerIf.cpp
    ${SRC_DIR}/BBController.cpp
    ${SRC_DIR}/PIDController.cpp
)

# Link Google Test to the test executable
target_link_libraries(${TESTS_NAME} PRIVATE
    gtest_main 
    gtest
    gmock_main
    gmock
)

# Include application's headers
target_include_directories(${TESTS_NAME} PUBLIC ${INC_DIR})

# Add the tests to CTest
include(GoogleTest)
gtest_discover_tests(${TESTS_NAME})
