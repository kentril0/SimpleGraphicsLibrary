/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_APPLICATION_H_
#define SGL_CORE_APPLICATION_H_

#include "SGL/core/Window.h"
#include "SGL/core/Timer.h"


namespace sgl
{
    /**
     * @brief Derive this class for convenience
     */
    class Application
    {
    public:
        
        Application();
        ~Application();
    
        void Run();
    
    protected:
        /** @brief Called once in "Run" function, before the main loop */
        virtual void Start() = 0;
        
        /** @brief Called each frame, before rendering */
        virtual void Update(float deltaTime) = 0;

        /** @brief Render call, called each frame */
        virtual void Render() = 0;
    
    protected:
        // TODO statically shared among more apps?
        std::unique_ptr<Window> m_Window;
    
        Timer m_StartTimer;    ///< Time elapsed after "Start()"

    private:
        float m_LastFrameTime{ 0.0 };
    };

} // namespace sgl

#endif // SGL_CORE_APPLICATION_H_
