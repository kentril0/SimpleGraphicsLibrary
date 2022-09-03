#include <SGL/opengl/VertexBuffer.h>

#include <memory>

#include <glad/glad.h>

#include <SGL/core/Log.h>


namespace sgl
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(
        uint32_t size, bool immutable)
    {
        return std::make_shared<VertexBuffer>(size, immutable);
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(
        const void* data, uint32_t size, bool immutable)
    {
        return std::make_shared<VertexBuffer>(data, size, immutable);
    }

    // =========================================================================

    VertexBuffer::VertexBuffer(uint32_t size, bool immutable)
    {
        SGL_FUNCTION();

        CreateBuffer();
        AllocateData(nullptr, size, immutable);
    }

    VertexBuffer::VertexBuffer(const void* data, uint32_t size, bool immutable)
    {
        SGL_FUNCTION();
        CreateBuffer();
        AllocateData(data, size, immutable);
    }

    VertexBuffer::~VertexBuffer()
    {
        SGL_FUNCTION();
        DeleteBuffer();
    }

    void VertexBuffer::CreateBuffer()
    {
        SGL_FUNCTION();
        glCreateBuffers(1, &m_ID);
    }

    void VertexBuffer::AllocateData(const void* data, uint32_t size, 
                                    bool immutable) const
    {
        SGL_FUNCTION();

        if (immutable)
            glNamedBufferStorage(m_ID, size, data, GL_DYNAMIC_STORAGE_BIT);
        else
        {
            const GLenum usage = data == nullptr ? GL_DYNAMIC_DRAW
                                                 : GL_STATIC_DRAW;
            glNamedBufferData(m_ID, size, data, usage);
        }
    }

    void VertexBuffer::DeleteBuffer()
    {
        SGL_FUNCTION();
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }

    void VertexBuffer::SetLayout(const BufferLayout& layout)
    {
        SGL_FUNCTION();
        m_Layout = layout;
    }

    void VertexBuffer::Bind() const
    {
        SGL_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void VertexBuffer::UnBind()
    {
        SGL_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::UpdateData(const void* data, uint32_t size,
                                  int32_t offset) const
    {
        SGL_FUNCTION();
        glNamedBufferSubData(m_ID, offset, size, data);
    }

} // namespace sgl
