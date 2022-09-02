#ifndef SGL_CORE_WINDOW_H_
#define SGL_CORE_WINDOW_H_

#include <string>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "SGL/core/Base.h"


namespace sgl
{
    // One place of change
    struct WindowData
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool VSync;

        WindowData(const std::string& title = SGL_WINDOW_DEFAULT_TITLE,
                   uint32_t width = SGL_WINDOW_DEFAULT_WIDTH,
                   uint32_t height = SGL_WINDOW_DEFAULT_HEIGHT)
            : title(title), width(width), height(height), VSync(true) {}
    };

    /**
     * Abstracts window and OpenGL context using GLFWWindow handle
     */
    class Window
    {
    public: 
        static std::unique_ptr<Window> Create(
            const WindowData& data = WindowData());
    public:
        Window(const WindowData& data = WindowData());
        ~Window();

        operator GLFWwindow*() const { return m_Window; }
        GLFWwindow* GetGLFWWindow() const { return m_Window; }

        bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

        /**
         * @brief Swaps buffers to display the rendered frame
         */
        void Display() const { glfwSwapBuffers(m_Window); }

        /**
         * @brief Processes pending events that have already been received, and
         *  returns immediately 
         */
        void PollEvents() const { glfwPollEvents(); }

        /**
         * @brief Destroys the window handle for it to be later created again
         */
        void DestroyWindow();

        uint32_t GetWidth() const { return m_Data.width; }
        uint32_t GetHeight() const { return m_Data.height; }

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }

        // Set callbacks
        
    
    private:
        void CreateWindow();

        static void InitGLFW();
        static void TerminateGLFW();
        static void LoadGL();

    private:
        GLFWwindow* m_Window{ nullptr };
        WindowData m_Data;

        static uint8_t s_WindowCount;
    };
}


#endif // SGL_CORE_WINDOW_H_