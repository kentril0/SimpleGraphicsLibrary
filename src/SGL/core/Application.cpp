/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/core/Application.h"


namespace sgl
{
    Application::Application()
    {
        SGL_FUNCTION();

        // TODO can be hidden until "Run()"
        m_Window = Window::Create();
    }

    Application::~Application()
    {
        SGL_FUNCTION();
    }

    void Application::Run()
    {
        SGL_FUNCTION();

        // TODO show window

        m_StartTimer.Start();

        Start();

        while ( m_Window->IsOpen() )
        {
            const float curTime = static_cast<float>(glfwGetTime());
            const sgl::Timestep dt(curTime - m_LastFrameTime);
            m_LastFrameTime = curTime;

            Update(dt);

            Render();

            m_Window->Display();
            m_Window->PollEvents();
        }

        // TODO hide window
    }

} // namespace sgl
