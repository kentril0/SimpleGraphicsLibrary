#pragma once
#include <SGL/SGL.h>


class HelloTriangle : public sgl::Application
{
public:
    HelloTriangle();
    ~HelloTriangle();

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

private:
    std::shared_ptr<sgl::VertexBuffer> m_VertexBuffer{ nullptr };
    std::shared_ptr<sgl::VertexArray> m_VertexArray{ nullptr };

    std::shared_ptr<sgl::Shader> m_Shader{ nullptr };
};
