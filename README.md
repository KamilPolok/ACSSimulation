# ACSSimulation - Automatic Control System Simulation

## Overview

The **ACSSimulation** library provides a modular and extensible framework for implementing various control algorithms. It allows for simulation of various scenarios using different controllers, control objects and actuators. The library is designed with flexibility in mind, enabling users to extend the capabilities to suit specific simulation requirements.

### **Caution!**

As of now (August 2024) the library is under constant development. There is a high propability of introducing breaking changes. Use it on your own risk.

## Setup Instructions

### Prerequisites

* CMake version 3.20. or higher
* C++ Compiler with C++17 support (e.g., GCC, Clang)
* Optional: AddressSanitizer (for debugging)

### Building the library

**1. Configure the project:**

```bash
cmake -DBUILD_SHARED_LIBS=<ON/OFF> -DCMAKE_BUILD_TYPE=<STATIC/SHARED> -B ./build -S .
```

Options:

* `-DBUILD_TESTS` - Build the unit tests.
* `-DBUILD_EXAMPLES` - Build the library usage examples
* `-DENABLE_ASAN` - Use Clang Adress Sanitizer for detecting memory leaks

**2. Build the library:**

```bash  
cmake --build . --target install 
```

## Examples and usage

To explore examples and usage of the library, refer to the [Examples README](./examples/README.md)

## Contributing

Contributions are welcome! Please fork the repository and create a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
