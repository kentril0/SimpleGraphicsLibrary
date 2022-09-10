
#include "VertexBuffers.h"


VertexBuffers::VertexBuffers()
{
    SGL_FUNCTION();

    InitializeRenderObjects();
}

VertexBuffers::~VertexBuffers()
{
    SGL_FUNCTION();
}

void VertexBuffers::InitializeRenderObjects()
{
    CreateVertexBuffers();
    CreateVertexArrays();
    CreateShaders();
}

void VertexBuffers::CreateVertexBuffers()
{
    CreateBuffersDiamond();
    CreateBuffersSquare();
    CreateBuffersTriangle();
}

void VertexBuffers::CreateVertexArrays()
{
    m_DiamondVAO = sgl::VertexArray::Create();
    m_DiamondVAO->AddVertexBuffer(m_DiamondPositionVBO);
    m_DiamondVAO->AddVertexBuffer(m_DiamondColorVBO);

    m_SquareVAO = sgl::VertexArray::Create();
    m_SquareVAO->AddVertexBuffer(m_SquareVBO);

    m_TriangleVAO = sgl::VertexArray::Create();
    m_TriangleVAO->AddVertexBuffer(m_TriangleVBO);
}

void VertexBuffers::CreateShaders()
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

void VertexBuffers::CreateBuffersDiamond()
{
    m_DiamondPositionVBO = sgl::VertexBuffer::Create(
        s_kDiamondPositions.data(),
        s_kDiamondPositions.size() * sizeof( decltype(s_kDiamondPositions[0]) )
    );
    m_DiamondPositionVBO->SetLayout({
        { sgl::ElementType::Float3, "Position" }
    });

    m_DiamondColorVBO = sgl::VertexBuffer::Create(
        s_kDiamondColors.data(),
        s_kDiamondColors.size() * sizeof( decltype(s_kDiamondColors[0]) )
    );
    m_DiamondColorVBO->SetLayout({
        { sgl::ElementType::Float3, "Color" }
    });
}

void VertexBuffers::CreateBuffersSquare()
{
    m_SquareVBO = sgl::VertexBuffer::Create(
        s_kSquareData.data(),
        s_kSquareData.size() * sizeof( decltype(s_kSquareData[0]) )
    );

    m_SquareVBO->SetLayout({
        { sgl::ElementType::Float3, "Position" },
        { sgl::ElementType::Float3, "Color", 
           sizeof( decltype(s_kSquareData[0]) )*3 * 6   // offset
        },
    });
}

void VertexBuffers::CreateBuffersTriangle()
{
    m_TriangleVBO = sgl::VertexBuffer::Create(
        s_kTriangleVertices.data(),
        s_kTriangleVertices.size() * sizeof( decltype(s_kTriangleVertices[0]) )
    );
    // Interleaved, normalized
    m_TriangleVBO->SetLayout({
        { sgl::ElementType::Float3, "Position" },
        { sgl::ElementType::UInt8_3, "Color" ,
          0,    // offset
          offsetof(VertexBuffers::Vertex, color),   // relativeOffset
          true  // normalized
        },
    });
}

void VertexBuffers::SetupPreRenderStates()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_Shader->Use();
}

void VertexBuffers::OnResize(GLFWwindow* window, int width, int height)
{
    sgl::WindowData& data = sgl::Window::GetUserData(window);
    data.width = width;
    data.height = height;
    
    glViewport(0, 0, width, height);
}

// =============================================================================

void VertexBuffers::Start()
{
    SetupPreRenderStates();

    m_Window->SetWindowSizeCallback(VertexBuffers::OnResize);
}

void VertexBuffers::Update(float dt)
{
    
}

void VertexBuffers::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_DiamondVAO->Bind();

    const uint32_t kAttribCount = 3;
    const uint32_t kVertexCount = s_kDiamondPositions.size() / kAttribCount;

    glDrawArrays(GL_TRIANGLES, 0, kVertexCount );

    m_SquareVAO->Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_TriangleVAO->Bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
