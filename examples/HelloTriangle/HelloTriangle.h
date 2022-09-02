#pragma once
#include <SGL/SGL.h>


class HelloTriangle : public sgl::Application
{
public:
    HelloTriangle();
    ~HelloTriangle();

protected:
    virtual void Update(float deltaTime) override;
    virtual void Render() override;

private:
    void InitializeRenderObjects();

    void CreateVertexBuffers();
    void CreateVertexArrays();
    void CreatePrograms();

    void SetupPreRenderStates();

private:
    std::shared_ptr<sgl::VertexBuffer> m_VertexBuffer{ nullptr };
    std::shared_ptr<sgl::VertexArray> m_VertexArray{ nullptr };

    // TODO Renamoe program to based on GL ref or for both vulkan
    std::shared_ptr<sgl::Program> m_Program{ nullptr };
};
