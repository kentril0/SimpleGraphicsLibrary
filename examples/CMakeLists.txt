

cmake_minimum_required(VERSION 3.16)
project(SGL_examples CXX)

message(STATUS "MAIN: ${CMAKE_SOURCE_DIR}")
#find_package(glfw3 REQUIRED)

if(NOT TARGET SGL)
    # Stand-alone build
    find_package(SGL REQUIRED)
endif()

# TODO function for each app

add_executable(HelloTriangle
    HelloTriangle/HelloTriangle.cpp
    main.cpp
)

#target_include_directories(HelloTriangle PRIVATE ${LGLW_INCLUDE_DIR})
target_include_directories(HelloTriangle PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(HelloTriangle PRIVATE SGL::SGL glfw)