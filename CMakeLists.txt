
cmake_minimum_required(VERSION 3.16)

set(SGL_VERSION "0.0")

project(SGL VERSION ${SGL_VERSION} )
message(STATUS "Building SGL version ${SGL_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ------------------------------------------------------------------------------
# Options
option(SGL_BUILD_STATIC "Build SGL as a static library" ON)
option(BUILD_EXAMPLES   "Build examples"                ON)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
# ------------------------------------------------------------------------------

if(SGL_BUILD_STATIC)
    set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

    # TODO INTO FUNCTIONS
    # make funcitons ltaer to try functionality with

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

    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)
    option(GLFW_DOCUMENT_INTERNALS OFF)

    set(GLFW_LIBRARIES 
      ${GLFW_BINARY_DIR}/src/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}
    )

    # Adds 'glfw' variable - the project name
    add_subdirectory(${GLFW_DIR} ${GLFW_BINARY_DIR} EXCLUDE_FROM_ALL)

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
    set(GLM_INCLUDE_DIR "${GLM_DIR}") 

    # --------------------------------------------------------------------------

    set(SGL_DIR "${CMAKE_SOURCE_DIR}/src/SGL")
    set(SGL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")

    set(SGL_CORE_DIR "${SGL_DIR}/core")
    set(SGL_OPENGL_DIR "${SGL_DIR}/opengl")

    set(SGL_SOURCES
        "${SGL_CORE_DIR}/Log.cpp" 
        "${SGL_CORE_DIR}/Window.cpp" 
        "${SGL_CORE_DIR}/Application.cpp" 
        "${SGL_OPENGL_DIR}/BufferLayout.cpp" 
        "${SGL_OPENGL_DIR}/VertexBuffer.cpp" 
        "${SGL_OPENGL_DIR}/IndexBuffer.cpp" 
        "${SGL_OPENGL_DIR}/VertexArray.cpp" 
        "${SGL_OPENGL_DIR}/ShaderObject.cpp" 
        "${SGL_OPENGL_DIR}/Shader.cpp" 
        "${SGL_DIR}/SGL.cpp"
    )

    add_library(${PROJECT_NAME} STATIC ${SGL_SOURCES})
    add_library(SGL::SGL ALIAS ${PROJECT_NAME})

    target_include_directories(${PROJECT_NAME}
        PUBLIC ${SGL_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} 
               ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR}
    )

    target_link_libraries(${PROJECT_NAME}
        PRIVATE spdlog::spdlog 
        PRIVATE ${GLAD_LIBRARIES}
        PRIVATE ${GLFW_LIBRARIES}
    )

endif()

if(BUILD_EXAMPLES)
    set(EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/examples")
    message(STATUS "Building examples")
    add_subdirectory(${EXAMPLES_DIR})
endif()