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

        /** 
         * @return Ref to WindowData saved as a user data ptr in the window handle
         * @pre Window must exist
         */
        static WindowData& GetUserData(GLFWwindow* w);

    public:
        Window(const WindowData& data = WindowData());
        ~Window();

        operator GLFWwindow*() const { return m_Window; }
        GLFWwindow* GetGLFWWindow() const { return m_Window; }

        inline bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

        /**
         * @brief Swaps buffers to display the rendered frame
         */
        inline void Display() const { glfwSwapBuffers(m_Window); }

        /**
         * @brief Processes pending events that have already been received, and
         *  returns immediately 
         */
        inline void PollEvents() const { glfwPollEvents(); }

        /**
         * @brief Destroys the window handle for it to be later created again
         */
        void DestroyWindow();

        void UpdateSize();

        uint32_t GetWidth() const { return m_Data.width; }
        uint32_t GetHeight() const { return m_Data.height; }

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }

        // Callbacks

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, int key, int scancode, int action,
         *             int mods)
         * Called when a key is pressed, repeated or released.
         */
        void SetKeyCallback(GLFWkeyfun callback) const;

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, int width, int height)
         * 
         * Called when the window is resized
         */
        void SetWindowSizeCallback(GLFWwindowsizefun callback) const;

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window)
         * 
         * Called when the user attempts to close the window
         */
        void SetWindowCloseCallback(GLFWwindowclosefun callback) const;

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, unsigned int codepoint)
         * 
         * Called when a Unicode character is input
         * Is keyboard layout dependent, characters do not map 1:1 to
         *  physical keys,
         */
        void SetCharCallback(GLFWcharfun callback) const;

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, int button, int action, int mods)
         * 
         * Called when a mouse button is pressed or released.
         */
        void SetMouseButtonCallback(GLFWmousebuttonfun callback) const;
        
        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, double xoffset, double yoffset)
         * 
         * Called when a scrolling device is used, such as a mouse wheel or
         *  scrolling area of a touchpad.
         */
        void SetScrollCallback(GLFWscrollfun callback) const;

        /**
         * @param callback Function of signature:
         *  void fname(GLFWwindow* window, double xpos, double ypos)
         * 
         * Called when the cursor is moved. The callback is provided with the
         *  position, in screen coordinates, relative to the upper-left corner
         *  of the content area of the window.
         */
        void SetCursorPosCallback(GLFWcursorposfun callback) const;
    
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