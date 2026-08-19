# LLogger

A small header-only logging framework for modern C++.

[![License: MIT](https://shields.io)](https://opensource.org)
[![Language: C++17](https://shields.io)](https://cppreference.com)

## Features

- **Header-Only:** Zero compilation setup. Just include and log.
- **Thread-Safe:** Uses `std::mutex` to ensure clean console outputs even in heavily multithreaded applications.
- **Zero-Copy Performance:** Leverages `std::string_view` to prevent unnecessary memory allocations.
- **Multiple Log Levels:** Supports `TRACE`, `DEBUG`, `INFO`, `WARNING`, and `ERROR`.
- **Log Formatting:** Allows parsing like `LOG_INFO("Llogger is {0} of the {1} frameworks!", 1, "best");`
- **Zero Third-Party Dependencies:** Only relies on the C++ Standard Library.

## Requirements

- **Compiler:** Any modern compiler with **C++17** support (e.g., GCC 7+, Clang 5+, MSVC 2017+).
- **Build System:** **CMake 3.14** or higher.

## Integration via CMake FetchContent

You can easily integrate `Llogger` into your project without cloning it manually. Just add the following lines to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
    llogger
    GIT_REPOSITORY https://github.com/Leo-64/LLogger.git
    GIT_TAG        main # You can also use a specific tag/commit hash here
)

FetchContent_MakeAvailable(llogger)

# Link it to your target
target_link_libraries(your_project_target PRIVATE llogger)
```

## Quick Start

## Building the Tests

If you want to clone this repository and run the built-in test suite:

## License

This project is licensed under the MIT License - see the LICENSE file for details.

