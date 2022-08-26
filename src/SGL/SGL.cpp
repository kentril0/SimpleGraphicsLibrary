#include "SGL/SGL.h"
#include "SGL/core/Log.h"
#include "SGL/Application/Window.h"

#include <memory>


namespace sgl
{
    void InitLogging();
    void InitGLFW();
    void LoadGLFunctions();
    
    void Init(bool debugGL)
    {
        InitLogging();
        InitGLFW();
        LoadGLFunctions();
    }

    void InitLogging()
    {
        sgl::Log::Init();
        SGL_FUNCTION();
    }

    void InitGLFW()
    {
        SGL_FUNCTION();

    }

    void LoadGLFunctions()
    {
        SGL_FUNCTION();

    }

    std::unique_ptr<sgl::Window> CreateWindow()
    {
        return std::make_unique<sgl::Window>();
    }

} // namespace sgl