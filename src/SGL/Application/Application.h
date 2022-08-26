#pragma once


namespace sgl
{
    class Application
    {
    public:
        Application();
        ~Application();
    
        void Run();
    
    protected:
        virtual void HandleInput() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
    
    protected:
        static const int DEFAULT_WIN_WIDTH = 800;
        static const int DEFAULT_WIN_HEIGHT = 600;
    
    private:
    
    };

} // namespace sgl
