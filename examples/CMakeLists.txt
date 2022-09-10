
cmake_minimum_required(VERSION 3.16)
project(SGL_examples CXX)

message(STATUS "Building Examples")

# TODO add here directories of examples

add_subdirectory(HelloTriangle/ ${CMAKE_SOURCE_DIR}/build/HelloTriangle)
add_subdirectory(VertexBuffers/ ${CMAKE_SOURCE_DIR}/build/VertexBuffers)
