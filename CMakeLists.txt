
cmake_minimum_required(VERSION 3.16)

set(GLW_VERSION "0.0")

project(GLW VERSION ${GLW_VERSION} )
message(STATUS "Building GLW version ${GLW_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(GLW_BUILD_STATIC "Build GLW as a static library" ON)
option(BUILD_EXAMPLES   "Build examples"                ON)

