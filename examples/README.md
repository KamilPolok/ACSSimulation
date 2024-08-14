# EXAMPLES AND USE CASES

This folder contains common use cases of the library.

## Using library in your own project

Building the library results in providing a package along with a config file: [ACSSimulationConfig.cmake](../install/cmake/ACSSimulationConfig.cmake).

To use the library in your own project you can follow the instructions provided in the [CMakeLists.txt](./CMakeLists.txt)

### Steps to Integrate the Library

**1. Set CMAKE_PREFIX_PATH:**

   Append the path to the config file to the `CMAKE_PREFIX_PATH` variable. This variable is treated as a list of base paths in which CMake searches for config files.

**2. Find the Package:**

   Use the `find_package()` command in your CMakeLists.txt file to locate and include the library.

Proceed with the rest of the instructions

## Build and Run Examples

**1. Enable Example Build:**

From the repository root, reconfigure the project with tests enabled:

```bash
cmake -DBUILD_TESTS=ON -B ./build -S .
```

**2. Build and Run:**

```bash
cmake --build . --target example_usage
./examples/example_usage
```
