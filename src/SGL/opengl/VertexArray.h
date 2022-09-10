#ifndef SGL_OPENGL_VERTEX_ARRAY_H_
#define SGL_OPENGL_VERTEX_ARRAY_H_

#include <cstdint>
#include <memory>
#include <vector>

#include <SGL/opengl/VertexBuffer.h>
#include <SGL/opengl/IndexBuffer.h>


namespace sgl
{
    class VertexArray
    {
    public:
        static std::shared_ptr<VertexArray> Create();

    public:
        VertexArray();
        ~VertexArray();

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo,
                             bool instancedAttribs = false);

        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);

        void Bind() const;
        static void UnBind();

        uint32_t GetID() const { return m_ID; }

        std::vector< std::shared_ptr<VertexBuffer> > GetVertexBuffers() const {
            return m_VertexBuffers;
        }
        std::shared_ptr<IndexBuffer> GetIndexBuffer() const {
            return m_IndexBuffer;
        };

    private:
        void CreateVertexArray();
        void DeleteVertexArray();

        void SpecifyVertexAttribute(const uint32_t kVboID,
                                    const uint32_t kStride,
                                    const BufferElement& kElement,
                                    const uint32_t kDivisor,
                                    const int32_t kComponentOffset = 0);

    private:
        uint32_t m_ID{ 0 };

        std::vector< std::shared_ptr<VertexBuffer> > m_VertexBuffers;
        uint32_t m_BindingIndex{ 0 };   ///< Binding index counter of attributes

        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };

    
} // namespace sgl

#endif // SGL_OPENGL_VERTEX_ARRAY_H_
