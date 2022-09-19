
Simple Graphics Library (SGL)
=============================

A simple library for learning and experimenting with Graphics APIs, written in C++.
For now, supports only OpenGL 4.5.

## Features:

* Abstractions of OpenGL objects for use under the RAII concept:
    * Shader, VertexBuffer, IndexBuffer, Texture2D, CubeMapTexture, etc
* Window abstraction using GLFW3
* Application base class for quick and clean prototyping
* Logging abstraction
* ImGui integration into Application base class

## Used Libraries:

* window abstraction: [GLFW3](https://github.com/glfw/glfw)
* OpenGL headers: [GLAD](https://glad.dav1d.de/)
* logging library: [SPDLOG](https://github.com/gabime/spdlog)
* math library: [GLM](https://github.com/g-truc/glm)
* gui library: [ImGui](https://github.com/ocornut/imgui/)
* image loading library: [STB](https://github.com/nothings/stb)

## How to Use

See _examples/_ directory.

Use '--recursive' when cloning.

Style used: [Google C++ Style](https://google.github.io/styleguide/cppguide.html)

Example of an app that uses Application as a base class:
```cpp
#define SGL_USE_IMGUI
#include <SGL/SGL.h>
Class HelloTriangle : public sgl::Application
{
...
protected:
    virtual void Start() override {
        m_Window->SetWindowSizeCallback(HelloTriangle::OnResize);
    }
    virtual void Update(float dt) override;
    virtual void Render() override {
        glClear(GL_COLOR_BUFFER_BIT);
        ...
    }
    virtual void OnImGuiRender() override {
        ImGui::ShowDemoWindow(&mybool);
    }
...
}
```

## License

Distributed under MIT License Copyright (c) 2022 authors

## Release Notes
### version 0.2
* Texture support:
    * image loading
    * Texture2D abstraction
* IndexBuffer abstraction
* TexturedQuad example
* code readability updates
* fixes to make the SGL usable as a library, not just a standalone project
* support for loading binary and text files
* ImGui integration, Application base class updates
* CubeMapTexture abstraction

### Version 0.1
* Window abstraction using GLFW
* GL function loading using GLAD
* Logging abstraction using SPDLOG, along with custom asserts
* Added GLM as math library
* VertexBuffer abstraction
* VertexArray abstraction
* Shaders abstraction
* Examples:
    * HelloTriangle
    * VertexBuffers
* other core modules:
    * Timer, Timestep
* Application base class