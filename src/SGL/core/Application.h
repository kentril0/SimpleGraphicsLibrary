/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_APPLICATION_H_
#define SGL_CORE_APPLICATION_H_

#include <memory> 
#include <vector> 

#include "SGL/core/Window.h"
#include "SGL/core/Timer.h"
#include "SGL/core/Timestep.h"
#include "SGL/core/ProfileTimer.h"

// Define SGL_USE_IMGUI macro to use ImGui

#ifdef SGL_USE_IMGUI
    #include <imgui/imgui.h>
    #include <imgui/backends/imgui_impl_glfw.h>
    #include <imgui/backends/imgui_impl_opengl3.h>

    #define START_IMGUI_FRAME() do {    \
        ImGui_ImplOpenGL3_NewFrame();   \
        ImGui_ImplGlfw_NewFrame();      \
        ImGui::NewFrame();              \
    } while(0)

    #define RENDER_IMGUI_FRAME() do {   \
        ImGui::Render();                \
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );   \
    } while(0)
#else
    #define START_IMGUI_FRAME()
    #define RENDER_IMGUI_FRAME()
#endif


// Profiling macros
// use SGL_PROFILE_SCOPE() , or
// use SGL_PROFILE_SCOPE("your description") 

#define SGL_PSCOPE1(name) sgl::ProfileTimer timer##__LINE__( \
    name, \
    [&](sgl::ProfileRecord result) { m_ProfileResults.push_back(result); })

#define SGL_PSCOPE0() sgl::ProfileTimer timer1##__LINE__( \
    __func__, \
    [&](sgl::ProfileRecord result) { m_ProfileResults.push_back(result); })

#define SGL_EXPAND_PSCOPE(_0,_1,fname, ...) fname

#define SGL_PROFILE_SCOPE(...) \
    SGL_EXPAND_PSCOPE(_0, ##__VA_ARGS__, SGL_PSCOPE1, SGL_PSCOPE0)(__VA_ARGS__)


namespace sgl
{
    /**
     * @brief Derive this class for convenience */
    class Application
    {
    public:
        Application();
        ~Application();
    
        void Run()
        {
            Init();
            Loop();
        }
    
    protected:
        /** @brief Called once in "Run" function, before the main loop */
        virtual void Start() = 0;
        
        /** @brief Called each frame, before rendering */
        virtual void Update(float deltaTime) = 0;

        /** @brief Render call, called each frame */
        virtual void Render() = 0;

    #ifdef SGL_USE_IMGUI
        /** @brief Called after Render() in ImGui frame */
        virtual void OnImGuiRender() = 0;
    #else
        virtual void OnImGuiRender() {}
    #endif
    
    protected:
        // TODO statically shared among more apps?
        std::unique_ptr<Window> m_Window;
    
        Timer m_StartTimer;    ///< Time elapsed after "Start()"
        std::vector<ProfileRecord> m_ProfileResults;

    private:
    #ifndef SGL_USE_IMGUI
        void CreateImGuiContext() {}
    #else
        /**
         * Creates ImGui Context AFTER glfw has been initialized, that is
         *  after the window has been created
         */
        void CreateImGuiContext() const
        {
            SGL_FUNCTION();
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWWindow(), true);
            ImGui_ImplOpenGL3_Init(SGL_GLSL_VERSION_STR);
        }
    #endif
        void Init()
        {
            m_StartTimer.Start();
            this->Start();
            CreateImGuiContext();
        }

        void Loop()
        {
            while ( m_Window->IsOpen() )
            {
                const float curTime = static_cast<float>(glfwGetTime());
                const sgl::Timestep dt(curTime - m_LastFrameTime);
                m_LastFrameTime = curTime;

                this->Update(dt);

                this->Render();

                START_IMGUI_FRAME();
                    this->OnImGuiRender();
                    ShowProfileResultsWindow();
                RENDER_IMGUI_FRAME();

                m_Window->Display();
                m_Window->PollEvents();
            }
        }

        #ifndef SGL_USE_IMGUI
            void ShowProfileResultsWindow() { m_ProfileResults.clear(); }
        #else
            void ShowProfileResultsWindow()
            {
                if (m_ProfileResults.size() == 0) { return; }
                ImGui::Begin("Profiling Results");
                for (const auto& result : m_ProfileResults)
                {
                    char label[64];
                    strcpy(label, "%.3f ms ");
                    strcat(label, result.name);
                    ImGui::Text(label, result.duration);
                }
                m_ProfileResults.clear();
                ImGui::End();
            }
        #endif

    private:
        float m_LastFrameTime{ 0.0 };
    };

} // namespace sgl


#endif // SGL_CORE_APPLICATION_H_
