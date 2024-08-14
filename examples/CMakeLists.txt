# Provide the path to library's installation folder, so CMake could find its config
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/install/cmake")
message(STATIC "${PROJECT_SOURCE_DIR}/install/cmake")

find_package(ACSSimulation CONFIG REQUIRED)

add_executable(example_usage)

target_sources(example_usage
    PRIVATE
        example_usage.cpp)

target_include_directories(example_usage
    PRIVATE
        ${PROJECT_SOURCE_DIR}/utils
)

# Link to the library
target_link_libraries(example_usage PRIVATE ACSSimulation)
