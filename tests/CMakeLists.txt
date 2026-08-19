cmake_minimum_required(VERSION 3.14)
project(LLoggerTests LANGUAGES CXX)

add_executable(llogger_tests main.cpp)

target_link_libraries(llogger_tests PRIVATE llogger)

