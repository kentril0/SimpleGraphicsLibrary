
#include "HelloTriangle.h"


HelloTriangle::HelloTriangle()
{
    SGL_FUNCTION();

    InitializeRenderObjects();
    SetupPreRenderStates();
}

HelloTriangle::~HelloTriangle()
{
    SGL_FUNCTION();
}

void HelloTriangle::InitializeRenderObjects()
{
    CreateVertexBuffers();
    CreateVertexArrays();
    CreatePrograms();
}

void HelloTriangle::SetupPreRenderStates()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_Program->Use();
    m_VertexArray->Bind();
}

void HelloTriangle::CreateVertexBuffers()
{
    const std::array kVerticesColors{
        // Vertex            // Color
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left  
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top   
    };

    m_VertexBuffer = sgl::VertexBuffer::Create(kVerticesColors.data(),
                                               kVerticesColors.size());

    m_VertexBuffer->SetLayout(
        { sgl::ElementType::Float3, "Position" },
        { sgl::ElementType::Float3, "Color" }
    );
}

void HelloTriangle::CreateVertexArrays()
{
    m_VertexArray = sgl::CreateVertexArray();

    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

void HelloTriangle::CreatePrograms()
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

    const auto vertShader = sgl::CreateShaderStage(
        sgl::ShaderStage::Vertex,
        vertexShaderSrc
    );

    const auto fragShader = sgl::CreateShaderStage(
        sgl::ShaderStage::Fragment,
        fragmentShaderSrc
    );

    m_Program = sgl::CreateProgram({ vertShader, fragShader });
}

// =============================================================================

void HelloTriangle::Update(float dt)
{

}

void HelloTriangle::Render()
{
    glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

    glClear(GL_COLOR_BUFFER_BIT);

    // TODO sizeof(verticesColors) / (sizeof(float) * 6)
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

