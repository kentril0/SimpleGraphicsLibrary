# Copyright (c) 2022 SGL authors Distributed under MIT License 
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.16)

set(SGL_VERSION "0.2")

project(SGL VERSION ${SGL_VERSION} )
message(STATUS "<SGL> version: ${SGL_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# ------------------------------------------------------------------------------
# Language Settings

# TODO set only when in develop
set(SGL_DEVELOP TRUE)

set(SGL_FLAGS_DEBUG "-DSGL_DEBUG -DSGL_ENABLE_ASSERTS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${SGL_FLAGS_DEBUG}")

# ------------------------------------------------------------------------------
# Options

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(SGL_STANDALONE TRUE)
endif()

option(SGL_BUILD_STATIC "Build SGL as a static library" ON)
option(SGL_BUILD_EXAMPLES "Build examples" ${SGL_STANDALONE})

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
# ------------------------------------------------------------------------------

if(SGL_BUILD_STATIC)
    set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

    # --------------------------------------------------------------------------
    # --------------------------------------------------------------------------
    # Dependencies

    if(UNIX)
        find_package(OpenGL REQUIRED)
        find_package(X11 REQUIRED)
        find_package(Threads REQUIRED)
    endif()

    # ------------------------------------------------------------
    # SPDLOG

    set(SPDLOG_DIR "${LIBS_DIR}/spdlog")
    set(SPDLOG_INCLUDE_DIR "${SPDLOG_DIR}/include")

    # Creates spdlog.a in its source tree
    add_subdirectory(${SPDLOG_DIR})

    # ------------------------------------------------------------
    # GLAD

    set(GLAD_DIR "${LIBS_DIR}/glad")
    set(GLAD_INCLUDE_DIR "${GLAD_DIR}/include")

    add_library(glad STATIC
        "${GLAD_INCLUDE_DIR}/glad/glad.h"
        "${GLAD_DIR}/src/glad.c"
    )
    target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR})

    set(GLAD_LIBRARIES)
    if(UNIX)
        set(GLAD_LIBRARIES glad ${CMAKE_DL_LIBS})
    else()
        set(GLAD_LIBRARIES glad)
    endif()

    # ------------------------------------------------------------
    # GLFW3

    set(GLFW_DIR "${LIBS_DIR}/glfw")
    set(GLFW_INCLUDE_DIR "${GLFW_DIR}/include")
    set(GLFW_BINARY_DIR "${BUILD_DIR}/glfw")

    set(GLFW_LIBRARY_TYPE "STATIC")
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)
    set(GLFW_DOCUMENT_INTERNALS OFF)

    add_subdirectory(${GLFW_DIR} ${GLFW_BINARY_DIR} EXCLUDE_FROM_ALL)

    set(GLFW_LIBRARIES glfw)
    if(UNIX)
        set(GLFW_LIBRARIES ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${X11_LIBRARIES}
                           ${X11_Xrandr_LIB} ${X11_Xcursor_LIB}
                           ${X11_Xinerama_LIB} ${X11_Xxf86vm_LIB}
                           ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS}
        )
    else()
        # TODO Windows and others
    endif()

    # ------------------------------------------------------------
    # GLM - header-only

    set(GLM_DIR "${LIBS_DIR}/glm")
    set(GLM_INCLUDE_DIR "${LIBS_DIR}") 

    # ------------------------------------------------------------
    # STB image - header-only

    set(STB_DIR "${LIBS_DIR}/stb")
    set(STB_INCLUDE_DIR "${LIBS_DIR}")

    #---------------------------------------------------------------------------
    # imGUI library

    set(IMGUI_INCLUDE_DIR "${LIBS_DIR}/imgui")

    add_library(imgui
        "${IMGUI_INCLUDE_DIR}/imgui.h"
        "${IMGUI_INCLUDE_DIR}/imgui.cpp"
        "${IMGUI_INCLUDE_DIR}/imconfig.h"
        "${IMGUI_INCLUDE_DIR}/imgui_internal.h"
        "${IMGUI_INCLUDE_DIR}/imstb_textedit.h"
        "${IMGUI_INCLUDE_DIR}/imstb_rectpack.h"
        "${IMGUI_INCLUDE_DIR}/imstb_truetype.h"
        "${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp"
        "${IMGUI_INCLUDE_DIR}/imgui_tables.cpp"
        "${IMGUI_INCLUDE_DIR}/imgui_demo.cpp"
        "${IMGUI_INCLUDE_DIR}/imgui_draw.cpp"
        "${IMGUI_INCLUDE_DIR}/backends/imgui_impl_glfw.h"
        "${IMGUI_INCLUDE_DIR}/backends/imgui_impl_glfw.cpp"
        "${IMGUI_INCLUDE_DIR}/backends/imgui_impl_opengl3.h"
        "${IMGUI_INCLUDE_DIR}/backends/imgui_impl_opengl3.cpp"
    )
    add_dependencies(imgui glfw glad)
    target_link_libraries(imgui
        ${GLFW_LIBRARIES}
        ${GLAD_LIBRARIES}
    )

    target_include_directories(imgui
        PRIVATE ${GLFW_INCLUDE_DIR}
        PRIVATE ${GLAD_INCLUDE_DIR}
        PUBLIC ${IMGUI_INCLUDE_DIR}
    )

    target_compile_options(imgui
      PRIVATE "-DIMGUI_IMPL_OPENGL_LOADER_GLAD"
    )

    # --------------------------------------------------------------------------
    # --------------------------------------------------------------------------

    set(SGL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/SGL")
    set(SGL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

    set(SGL_CORE_DIR "${SGL_DIR}/core")
    set(SGL_OPENGL_DIR "${SGL_DIR}/opengl")

    set(SGL_SOURCES
        "${SGL_CORE_DIR}/Log.cpp" 
        "${SGL_CORE_DIR}/Utils.cpp" 
        "${SGL_CORE_DIR}/Window.cpp" 
        "${SGL_CORE_DIR}/Application.cpp" 
        "${SGL_OPENGL_DIR}/BufferLayout.cpp" 
        "${SGL_OPENGL_DIR}/VertexBuffer.cpp" 
        "${SGL_OPENGL_DIR}/IndexBuffer.cpp" 
        "${SGL_OPENGL_DIR}/VertexArray.cpp" 
        "${SGL_OPENGL_DIR}/ShaderObject.cpp" 
        "${SGL_OPENGL_DIR}/Shader.cpp" 
        "${SGL_OPENGL_DIR}/Texture2D.cpp" 
        "${SGL_OPENGL_DIR}/CubeMapTexture.cpp" 
        "${SGL_DIR}/SGL.cpp"
    )

    add_library(${PROJECT_NAME} STATIC ${SGL_SOURCES})
    add_library(SGL::SGL ALIAS ${PROJECT_NAME})

    target_include_directories(${PROJECT_NAME}
        PUBLIC ${SGL_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} 
               ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${STB_INCLUDE_DIR}
               ${IMGUI_INCLUDE_DIR}
    )

    target_link_libraries(${PROJECT_NAME}
        PRIVATE spdlog
        PRIVATE ${GLAD_LIBRARIES}
        PRIVATE ${GLFW_LIBRARIES}
        PRIVATE imgui
    )

    target_precompile_headers( ${PROJECT_NAME} PRIVATE "${SGL_DIR}/pch.h" )

    if(SGL_DEVELOP)
        set_target_properties( ${PROJECT_NAME} PROPERTIES
            COMPILE_FLAGS "${SGL_FLAGS_DEBUG}"
        )
    endif()

endif()

if(SGL_BUILD_EXAMPLES)
    set(EXAMPLES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    message(STATUS "Building examples")
    add_subdirectory(${EXAMPLES_DIR})
endif()
