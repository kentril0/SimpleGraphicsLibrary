/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#define SGL_DEBUG
#define SGL_ENABLE_ASSERTS
#include "TexturedQuad.h"
#include <glm/gtx/string_cast.hpp>


TexturedQuad::TexturedQuad()
{
    SGL_FUNCTION();

    InitializeRenderObjects();
}

TexturedQuad::~TexturedQuad()
{
    SGL_FUNCTION();
}

void TexturedQuad::InitializeRenderObjects()
{
    CreateVertexBuffers();
    CreateIndexBuffer();
    CreateVertexArrays();
    CreateShaders();
    CreateTextures();
}

void TexturedQuad::CreateVertexBuffers()
{
    m_VertexBuffer = sgl::VertexBuffer::Create(
        s_kVertices.data(),
        s_kVertices.size() * sizeof( decltype(s_kVertices[0]) )
    );

    m_VertexBuffer->SetLayout({
        { sgl::ElementType::Float2, "Position" },
        { sgl::ElementType::Float3, "Color",
          0, // offset
          offsetof(TexturedQuad::Vertex, color) // relativeOffset
        },
        { sgl::ElementType::Float2, "TexCoord",
          0, // offset
          offsetof(TexturedQuad::Vertex, texCoord) // relativeOffset
        },
    });
}

void TexturedQuad::CreateIndexBuffer()
{
    m_IndexBuffer = sgl::IndexBuffer::Create(indices.data(), indices.size());
}

void TexturedQuad::CreateVertexArrays()
{
    m_VertexArray = sgl::VertexArray::Create();

    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

void TexturedQuad::CreateShaders()
{
    const char* vertexShaderSrc = R"(
        #version 450 core
        layout(location = 0) in vec2 inPosition;
        layout(location = 1) in vec3 inColor;
        layout(location = 2) in vec2 inTexCoord;

        layout(location = 0) out vec3 fragColor;
        layout(location = 1) out vec2 fragTexCoord;

        uniform mat4 model;

        void main()
        {
            gl_Position = model * vec4(inPosition, 0.0, 1.0);
            fragColor = inColor;
            fragTexCoord = inTexCoord;
        };
    )";

    const char* fragmentShaderSrc = R"(
        #version 450 core
        layout(location = 0) in vec3 fragColor;
        layout(location = 1) in vec2 fragTexCoord;

        layout(location = 0) out vec4 outColor;

        layout(binding = 1) uniform sampler2D texSampler;

        void main()
        {
            outColor = vec4(texture(texSampler, fragTexCoord).rgb, 1.0);
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

void TexturedQuad::CreateTextures()
{
    const int kForceRGBA = 4;
    auto data = sgl::LoadImage(s_kTextureName, kForceRGBA);

    SGL_ASSERT_MSG(data.Loaded(), "Texture loaded: {}", bool(data));

    // TODO format based on component count and type
    m_Texture = sgl::Texture2D::Create({
        data.width, data.height, data.data,
        GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, true
    });
}

void TexturedQuad::SetupPreRenderStates()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_Shader->Use();

    SGL_LOG_INFO("Model:\n{}\n{}\n{}", 
                 glm::to_string(m_Model[0]),
                 glm::to_string(m_Model[1]),
                 glm::to_string(m_Model[2])
    );
    m_Shader->SetMat4("model", m_Model);

    m_VertexArray->Bind();
    m_Texture->BindUnit(1);
}

void TexturedQuad::OnResize(GLFWwindow* window, int width, int height)
{
    sgl::WindowData& data = sgl::Window::GetUserData(window);
    data.width = width;
    data.height = height;
    
    glViewport(0, 0, width, height);
}

// =============================================================================

void TexturedQuad::Start()
{
    SetupPreRenderStates();

    m_Window->SetWindowSizeCallback(TexturedQuad::OnResize);
}

void TexturedQuad::Update(float dt)
{
    static const glm::vec3 kZ_axis(0.0, 0.0, 1.0);

    const float kAngle = 30.0f * dt;

    m_Model = glm::rotate(m_Model, glm::radians(kAngle), kZ_axis);
}

void TexturedQuad::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shader->SetMat4("model", m_Model);

    glDrawElements(GL_TRIANGLES,
                   m_IndexBuffer->GetIndicesCount(),
                   m_IndexBuffer->GetIndexType(), 0);
}
