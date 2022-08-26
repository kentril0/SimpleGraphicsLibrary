#include "SGL/Application/Application.h"
#include "SGL/core/Log.h"


namespace sgl
{
    Application::Application()
    {
        SGL_FUNCTION();

    }

    Application::~Application()
    {
        SGL_FUNCTION();

    }

    void Application::Run()
    {
        SGL_FUNCTION();

        //m_Window = sgl::CreateWindow();

        float dt = 0;

        while (dt < 2.0) //( sgl::WindowNotClosed() )
        {
            //sgl::PollEvents();

            HandleInput();

            Update(dt);

            Render();

            // sgl::SwapBuffers();

            dt += 1.0;
        }
    }


} // namespace sgl
