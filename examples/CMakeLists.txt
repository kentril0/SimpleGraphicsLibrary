# Copyright (c) 2022 SGL authors Distributed under MIT License 
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.16)
project(SGL_examples CXX)

# TODO add here directories of examples
add_subdirectory(HelloTriangle/ ${CMAKE_SOURCE_DIR}/build/HelloTriangle)
add_subdirectory(VertexBuffers/ ${CMAKE_SOURCE_DIR}/build/VertexBuffers)
