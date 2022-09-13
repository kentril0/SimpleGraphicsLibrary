/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#pragma once
#include <SGL/SGL.h>


class TexturedQuad : public sgl::Application
{
public:
    TexturedQuad();
    ~TexturedQuad();

protected:
    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

private:
    void LoadTextures();
    void InitializeRenderObjects();

    void CreateVertexBuffers();
    void CreateIndexBuffer();
    void CreateVertexArrays();
    void CreateShaders();
    void CreateTextures();

    void SetupPreRenderStates();

    static void OnResize(GLFWwindow* window, int width, int height);

private:

    struct Vertex
    {
        glm::vec2 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
    };

    // TODO check texCoords diff
    static constexpr std::array s_kVertices{
        Vertex{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // bottom left
        Vertex{{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // bottom right
        Vertex{{ 0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // top right
        Vertex{{-0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // top left
    };

    static constexpr std::array<uint32_t, 6> indices{
        0, 1, 2, 2, 3, 0
    };

    std::shared_ptr<sgl::VertexBuffer> m_VertexBuffer{ nullptr };
    std::shared_ptr<sgl::IndexBuffer> m_IndexBuffer{ nullptr };

    std::shared_ptr<sgl::VertexArray> m_VertexArray{ nullptr };

    std::shared_ptr<sgl::Shader> m_Shader{ nullptr };

    glm::mat4 m_Model{ 1.0 };

    static inline const char* s_kTextureName = "textures/texture.jpg";
    std::shared_ptr<sgl::Texture2D> m_Texture{ nullptr };
};
