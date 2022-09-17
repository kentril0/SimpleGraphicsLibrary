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

#if 0
    void Application::Run()
    {
        SGL_FUNCTION();

        // TODO show window

        CreateImGuiContext();

        m_StartTimer.Start();

        this->Start();

        while ( m_Window->IsOpen() )
        {
            const float curTime = static_cast<float>(glfwGetTime());
            const sgl::Timestep dt(curTime - m_LastFrameTime);
            m_LastFrameTime = curTime;

            this->Update(dt);

            this->Render();

            START_IMGUI_FRAME();
                this->OnImGuiRender();
            RENDER_IMGUI_FRAME();

            m_Window->Display();
            m_Window->PollEvents();
        }
        // TODO hide window
    }
#endif

} // namespace sgl
