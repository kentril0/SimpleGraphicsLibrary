/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "HelloTriangle.h"


HelloTriangle::HelloTriangle()
{
    SGL_FUNCTION();

    InitializeRenderObjects();
}

HelloTriangle::~HelloTriangle()
{
    SGL_FUNCTION();
}

void HelloTriangle::InitializeRenderObjects()
{
    CreateVertexBuffers();
    CreateVertexArrays();
    CreateShaders();
}

void HelloTriangle::CreateVertexBuffers()
{
    m_VertexBuffer = sgl::VertexBuffer::Create(
        s_kVerticesColors.data(),
        s_kVerticesColors.size() * sizeof( decltype(s_kVerticesColors[0]) )
    );

    m_VertexBuffer->SetLayout({
        { sgl::ElementType::Float3, "Position" },
        { sgl::ElementType::Float3, "Color" }
    });
}

void HelloTriangle::CreateVertexArrays()
{
    m_VertexArray = sgl::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

void HelloTriangle::CreateShaders()
{
    const char* vertexShaderSrc = R"(
        #version 450 core
        layout (location = 0) in vec3 vPos;
        layout (location = 1) in vec3 vColor;
        out vec3 fColor;
        void main()
        {
            fColor = vColor;
            gl_Position = vec4(vPos, 1.0);
        };
    )";

    const char* fragmentShaderSrc = R"(
        #version 450 core
        in vec3 fColor;
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(fColor, 1.0);
        };
    )";

    const auto vertShader = sgl::ShaderObject::Create(
        sgl::ShaderStage::Vertex,
        vertexShaderSrc
    );

    const auto fragShader = sgl::ShaderObject::Create(
        sgl::ShaderStage::Fragment,
        fragmentShaderSrc
    );

    m_Shader = sgl::Shader::Create({ vertShader, fragShader });
}

void HelloTriangle::SetupPreRenderStates()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_Shader->Use();
    m_VertexArray->Bind();
}

void HelloTriangle::OnResize(GLFWwindow* window, int width, int height)
{
    sgl::WindowData& data = sgl::Window::GetUserData(window);
    data.width = width;
    data.height = height;
    
    glViewport(0, 0, width, height);
}

// =============================================================================

void HelloTriangle::Start()
{
    SetupPreRenderStates();

    m_Window->SetWindowSizeCallback(HelloTriangle::OnResize);
}

void HelloTriangle::Update(float dt)
{

}

void HelloTriangle::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // sizeof(verticesColors) / (sizeof(float) * 6)
    const uint32_t kAttribCount = 2 * 3;
    const uint32_t kVertexCount = s_kVerticesColors.size() / kAttribCount;

    glDrawArrays(GL_TRIANGLES, 0, kVertexCount);
}
