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

} // namespace sgl
