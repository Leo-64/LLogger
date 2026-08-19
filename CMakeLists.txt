cmake_minimum_required(VERSION 3.14)
project(LLogger VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(llogger INTERFACE)

target_include_directories(llogger INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(llogger INTERFACE cxx_std_17)

option(BUILD_TESTING "Build the testing suite" ON)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

