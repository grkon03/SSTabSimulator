cmake_minimum_required(VERSION 3.1)

project(SSTabSimulator)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SSTITargets *.cpp)

add_library(SSTabIncludes ${SSTITargets})