

cmake_minimum_required(VERSION 3.16)
project(HelloTriangle CXX)

message(STATUS "Example: HelloTriangle")

if(NOT TARGET SGL)
    # Stand-alone build
    find_package(SGL REQUIRED)
endif()

add_executable(${PROJECT_NAME} HelloTriangle.cpp main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SGL::SGL glfw)
