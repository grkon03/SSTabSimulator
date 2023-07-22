cmake_minimum_required(VERSION 3.1)

project(SSTabSimulator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(includes)

add_executable(SSTabSimulator main.cpp)

target_link_libraries(SSTabSimulator SSTabIncludes)