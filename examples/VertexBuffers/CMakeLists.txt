# Copyright (c) 2022 SGL authors Distributed under MIT License 
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.16)
project(VertexBuffers CXX)

message(STATUS "Example: VertexBuffers")

if(NOT TARGET SGL)
    # Stand-alone build
    find_package(SGL REQUIRED)
endif()

add_executable(${PROJECT_NAME} VertexBuffers.cpp main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SGL::SGL)
