/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/SGL.h"

#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "SGL/core/Log.h"
#include "SGL/core/Assert.h"
#include "SGL/core/Window.h"


namespace sgl
{
    // -------------------------------------------------------------------------
    // Function prototypes

    void InitLogging();

    // -------------------------------------------------------------------------
    
    void Init()
    {
        InitLogging();
    }

    void InitLogging()
    {
        sgl::Log::Init();
        SGL_FUNCTION();
    }


} // namespace sgl