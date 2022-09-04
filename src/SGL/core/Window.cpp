#include "SGL/core/Window.h"

#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "SGL/core/Log.h"
#include "SGL/core/Base.h"
#include "SGL/core/Assert.h"


namespace sgl
{
    uint8_t Window::s_WindowCount = 0;

    std::unique_ptr<Window> Window::Create(const WindowData& data)
    {
        SGL_FUNCTION();
        return std::make_unique<Window>(data);
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

    void Window::SetVSync(bool enabled)
    {
        SGL_FUNCTION();

        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    // =========================================================================

    static void GLFWErrorCallback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
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
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Window::TerminateGLFW()
    {
        SGL_FUNCTION();

        if (s_WindowCount == 0)
            glfwTerminate();
    }

    void Window::LoadGL()
    {
        SGL_FUNCTION();

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SGL_ASSERT_MSG(success, "Could not load OpenGL using GLAD");
    }

} // namespace sgl