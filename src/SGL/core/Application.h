#pragma once

#include "SGL/core/Window.h"


namespace sgl
{
    class Application
    {
    public:
        Application();
        ~Application();
    
        void Run();
    
    protected:
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
    
    protected:
        std::unique_ptr<Window> m_Window;
    
    private:
        float m_LastFrameTime{ 0.0 };
    
    };

} // namespace sgl
