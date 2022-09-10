#pragma once
#include <SGL/SGL.h>


class VertexBuffers : public sgl::Application
{
public:
    VertexBuffers();
    ~VertexBuffers();

protected:
    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

private:
    static void OnResize(GLFWwindow* window, int width, int height);

    void InitializeRenderObjects();

    void CreateVertexBuffers();
    void CreateVertexArrays();
    void CreateShaders();

    void SetupPreRenderStates();

    void CreateBuffersDiamond();
    void CreateBuffersSquare();
    void CreateBuffersTriangle();

private:
    std::shared_ptr<sgl::Shader> m_Shader{ nullptr };

    std::shared_ptr<sgl::VertexArray> m_DiamondVAO{ nullptr };
    std::shared_ptr<sgl::VertexArray> m_SquareVAO{ nullptr };
    std::shared_ptr<sgl::VertexArray> m_TriangleVAO{ nullptr };

    std::shared_ptr<sgl::VertexBuffer> m_DiamondPositionVBO{ nullptr };
    std::shared_ptr<sgl::VertexBuffer> m_DiamondColorVBO{ nullptr };
    std::shared_ptr<sgl::VertexBuffer> m_SquareVBO{ nullptr };
    std::shared_ptr<sgl::VertexBuffer> m_TriangleVBO{ nullptr };

    // -------------------------------------------------------------------------
    // Data

    static constexpr std::array<float, 4*3*3> s_kDiamondPositions{
        -0.5,  0.5,  0.6,
        -0.5,  0.75, 0.6,
        -0.75, 0.5,  0.6,
        //
        -0.5,  0.5,  0.6,
        -0.25, 0.5,  0.6,
        -0.5,  0.75, 0.6,
        //
        -0.5,  0.5,  0.6, 
        -0.25, 0.5,  0.6,
        -0.5,  0.25, 0.6,
        //
        -0.5,  0.5,  0.6,
        -0.5,  0.25, 0.6,
        -0.75, 0.5,  0.6,
    };

    static constexpr std::array<float, s_kDiamondPositions.size()> 
        s_kDiamondColors{
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
    };

    static constexpr std::array<float, 4*3*3> s_kSquareData{
        // Positions
        0.0, 0.25, 0.5,
        0.5, 0.25, 0.5,
        0.5, 0.75, 0.5,
        0.0, 0.25, 0.5,
        0.5, 0.75, 0.5,
        0.0, 0.75, 0.5,
        // Colors
        0.7, 0.0, 0.0,
        0.7, 0.0, 0.0,
        0.7, 0.0, 0.0,
        0.7, 0.0, 0.0,
        0.7, 0.0, 0.0,
        0.7, 0.0, 0.0,
    };

    // Triangle - with custom vertex type

    #pragma pack(push, 1)   // due to uint8_t
    struct Vertex
    {
      float position[3];
      uint8_t color[3]; // is uint8_t - needs relative offset, 
                        // also needs to be normalized
    };
    #pragma pack(pop)

    static constexpr std::array s_kTriangleVertices {
        Vertex{{-0.25, -0.5, 0.5}, {255, 0, 0}},
        Vertex{{0.25, -0.5, 0.5}, {0, 255, 0}},
        Vertex{{0.0, 0.0, 0.5}, {0, 0, 255}}
    };

};
