/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/core/Window.h"


namespace sgl
{
    uint8_t Window::s_WindowCount = 0;

    std::unique_ptr<Window> Window::Create(const WindowData& data)
    {
        SGL_FUNCTION();
        return std::make_unique<Window>(data);
    }

    WindowData& Window::GetUserData(GLFWwindow* w)
    {
        return *(sgl::WindowData*)glfwGetWindowUserPointer(w);
    }

    // =========================================================================

    Window::Window(const WindowData& data)
        : m_Data(data)
    {
        SGL_FUNCTION();

        InitGLFW();
        CreateWindow();

        glfwMakeContextCurrent(m_Window);

        // TODO Load GL only once?
        LoadGL();

        SetUserPointer(&m_Data);

        SetVSync(true);
    }

    void Window::CreateWindow()
    {
        SGL_FUNCTION();

        m_Window = glfwCreateWindow(m_Data.width, m_Data.height,
                                    m_Data.title.c_str(), nullptr, nullptr);
        SGL_ASSERT_MSG(m_Window != nullptr, 
                       "Window or OpenGL context creation failed");
    
        ++s_WindowCount;
    }

    Window::~Window()
    {
        SGL_FUNCTION();

        DestroyWindow();
        TerminateGLFW();
    }

    void Window::DestroyWindow()
    {
        SGL_FUNCTION();

        if (m_Window == nullptr)
            return;

        glfwDestroyWindow(m_Window);
        m_Window = nullptr;

        --s_WindowCount;
    }

    void Window::UpdateSize()
    {
        SGL_FUNCTION();

        int width, height;
        glfwGetFramebufferSize(m_Window, &width, &height);

        m_Data.width = static_cast<uint32_t>(width);
        m_Data.height = static_cast<uint32_t>(height);
    }

    void Window::SetVSync(bool enabled)
    {
        SGL_FUNCTION();

        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    void Window::SetUserPointer(void* ptr) const
    {
        glfwSetWindowUserPointer(m_Window, ptr);
    }

    void Window::SetKeyCallback(GLFWkeyfun callback) const
    {
        SGL_FUNCTION();
        glfwSetKeyCallback(m_Window, callback);
    }

    void Window::SetWindowSizeCallback(GLFWwindowsizefun callback) const
    {
        SGL_FUNCTION();
        glfwSetWindowSizeCallback(m_Window, callback);
    }

    void Window::SetWindowCloseCallback(GLFWwindowclosefun callback) const
    {
        SGL_FUNCTION();
        glfwSetWindowCloseCallback(m_Window, callback);
    }

    void Window::SetCharCallback(GLFWcharfun callback) const
    {
        SGL_FUNCTION();
        glfwSetCharCallback(m_Window, callback);
    }

    void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) const
    {
        SGL_FUNCTION();
        glfwSetMouseButtonCallback(m_Window, callback);
    }

    void Window::SetScrollCallback(GLFWscrollfun callback) const
    {
        SGL_FUNCTION();
        glfwSetScrollCallback(m_Window, callback);
    }

    void Window::SetCursorPosCallback(GLFWcursorposfun callback) const
    {
        SGL_FUNCTION();
        glfwSetCursorPosCallback(m_Window, callback);
    }

    // =========================================================================

    static void GLFWErrorCallback(int error, const char* description)
    {
        SGL_LOG_ERR("GLFW Error {0}: {1}\n", error, description);
    }

    void Window::InitGLFW()
    {
        SGL_FUNCTION();

        if (s_WindowCount > 0)
            return;

        glfwSetErrorCallback(GLFWErrorCallback);

        int success = glfwInit();
        SGL_ASSERT_MSG(success, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SGL_GL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SGL_GL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef SGL_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    #endif
    }

    void Window::TerminateGLFW()
    {
        SGL_FUNCTION();

        if (s_WindowCount == 0)
        {
            SGL_LOG_WARN("Shutting down GLFW, make sure no GL call happens"     
                         " after!");
            glfwTerminate();
        }
    }

#ifdef SGL_DEBUG
    static void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
                                       GLenum severity, GLsizei length, 
                                       const char *message,
                                       const void *user_parameter)
    {
        switch(type)
        {
            case GL_DEBUG_TYPE_ERROR:
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                SGL_LOG_ERR("{}", message);
                return;
            default:
                return;
        }
    }
#endif  // SGL_DEBUG

    void Window::LoadGL()
    {
        SGL_FUNCTION();

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SGL_ASSERT_MSG(success, "Could not load OpenGL using GLAD");

    #ifdef SGL_DEBUG
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugCallback, nullptr);
        SGL_LOG_INFO("Enabled OpenGL Debug context");
    #endif
    }

} // namespace sgl