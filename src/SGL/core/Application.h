/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_APPLICATION_H_
#define SGL_CORE_APPLICATION_H_

// TODO optionally define the following macros before including this header file:
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// * SGL_USE_IMGUI to use ImGui abstraction
// * SGL_PROFILE to enable recording profiling data

#include <memory> 
#include <vector> 

#include "SGL/core/Window.h"
#include "SGL/core/Timer.h"
#include "SGL/core/Timestep.h"
#include "SGL/core/Profile.h"

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
        Timer m_StartTimer;                 ///< Time elapsed after "Start()"

        // TODO statically shared among more apps?
        std::unique_ptr<Window> m_Window;
    
        float m_LastFrameTime{ 0.0 };

    #ifdef SGL_USE_IMGUI
        // Status window: shows FPS, frametimes and recorded profiling data
        bool m_ShowStatusWindow{ true };    ///< True to show ImGui status window
    #endif

    // =========================================================================
    // Application internal stuff

    private:

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

            #ifdef SGL_USE_IMGUI
                START_IMGUI_FRAME();
                    this->OnImGuiRender();

                    if (m_ShowStatusWindow)
                        ShowStatusWindow();
                RENDER_IMGUI_FRAME();
            #endif

                m_Window->Display();
                m_Window->PollEvents();
            }
        }

    #ifndef SGL_USE_IMGUI
        void CreateImGuiContext() const {}
        void ShowStatusWindow() {}
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

        void ShowStatusWindow()
        {
            if ( !ImGui::Begin("Application Metrics", &m_ShowStatusWindow) )
            {
                ImGui::End();
                return;
            }

            // Show frametime and FPS
            const ImGuiIO& io = ImGui::GetIO();
            const float kFrameTime = 1000.0f / io.Framerate;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                         kFrameTime, io.Framerate);
            ImGui::NewLine();

        #ifdef SGL_PROFILE
            ShowProfileRecordsTable();
        #endif

            ImGui::End();
        }

        void ShowProfileRecordsTable() const
        {
            ImGui::Text("Profiling data");
            if ( ImGui::BeginTable("Profiling data", 2,
                                    ImGuiTableFlags_Resizable |
                                    ImGuiTableFlags_BordersOuter |
                                    ImGuiTableFlags_BordersV) )
            {
                const auto& kRecords = sgl::Profile::GetRecordsFromLatest();
                for (const auto& record : kRecords)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%.3f ms", record.duration);
                    ImGui::TableNextColumn();
                    ImGui::Text("%s::%s", record.fileName, record.name);
                }
                ImGui::EndTable();
            }
        }
    #endif
    };

} // namespace sgl


#endif // SGL_CORE_APPLICATION_H_
