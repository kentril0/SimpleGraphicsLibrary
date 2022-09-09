
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
    // TODO should be static??
    static const std::array kVerticesColors{
        // Vertex            // Color
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left  
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top   
    };

    m_VertexBuffer = sgl::VertexBuffer::Create(
        kVerticesColors.data(),
        kVerticesColors.size() * sizeof( decltype(kVerticesColors[0]) )
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
    // TODO better
    sgl::WindowData* data = (sgl::WindowData*)glfwGetWindowUserPointer(window);
    data->width = width;
    data->height = height;
    
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

    // TODO sizeof(verticesColors) / (sizeof(float) * 6)
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

