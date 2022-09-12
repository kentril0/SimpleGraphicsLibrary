/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "TexturedQuad.h"


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
    CreateVertexArrays();
    CreateShaders();
}

void TexturedQuad::CreateVertexBuffers()
{
    
}

void TexturedQuad::CreateVertexArrays()
{
    
}

void TexturedQuad::CreateShaders()
{
    
}

void TexturedQuad::SetupPreRenderStates()
{
    
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

}

void TexturedQuad::Render()
{
    
}
