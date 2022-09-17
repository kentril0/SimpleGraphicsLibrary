/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_APPLICATION_H_
#define SGL_CORE_APPLICATION_H_

#include "SGL/core/Window.h"
#include "SGL/core/Timer.h"
#include "SGL/core/Timestep.h"

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
     * @brief Derive this class for convenience
     */
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
        // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // Enable Gamepad Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWWindow(), true);
        ImGui_ImplOpenGL3_Init(SGL_GLSL_VERSION_STR);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
        }
    #endif
        void Init()
        {
            CreateImGuiContext();
            m_StartTimer.Start();
            this->Start();
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
                RENDER_IMGUI_FRAME();

                m_Window->Display();
                m_Window->PollEvents();
            }
        }

    private:
        float m_LastFrameTime{ 0.0 };
    };

} // namespace sgl


#endif // SGL_CORE_APPLICATION_H_
