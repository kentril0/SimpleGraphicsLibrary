/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#pragma once
#include <SGL/SGL.h>


class ImGuiTriangle : public sgl::Application
{
public:
    ImGuiTriangle();
    ~ImGuiTriangle();

protected:
    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

private:
    void InitializeRenderObjects();

    void CreateVertexBuffers();
    void CreateVertexArrays();
    void CreateShaders();

    void SetupPreRenderStates();

    // TODO better
    static void OnResize(GLFWwindow* window, int width, int height);

private:

    static constexpr std::array s_kVerticesColors{
        // Vertex            // Color
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top
    };

    std::shared_ptr<sgl::VertexBuffer> m_VertexBuffer{ nullptr };
    std::shared_ptr<sgl::VertexArray> m_VertexArray{ nullptr };

    std::shared_ptr<sgl::Shader> m_Shader{ nullptr };
};
