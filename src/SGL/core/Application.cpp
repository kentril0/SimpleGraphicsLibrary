#include "SGL/core/Application.h"

#include "SGL/core/Log.h"
#include "SGL/core/Timestep.h"


namespace sgl
{
    Application::Application()
    {
        SGL_FUNCTION();
        m_Window = Window::Create( {"Application"} );
    }

    Application::~Application()
    {
        SGL_FUNCTION();
    }

    void Application::Run()
    {
        SGL_FUNCTION();


        // TODO
        //OnInit();

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

        m_Window->DestroyWindow();
    }

} // namespace sgl
