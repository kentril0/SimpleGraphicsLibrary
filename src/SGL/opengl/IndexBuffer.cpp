/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include <SGL/opengl/IndexBuffer.h>

#include <glad/glad.h>

#include <SGL/core/Log.h>


namespace sgl
{
    IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t indicesCount)
        : m_IndicesCount(indicesCount)
    {
        SGL_FUNCTION();

        glCreateBuffers(1, &m_ID);

        glNamedBufferStorage(m_ID,
                             indicesCount * sizeof(uint32_t),
                             indices,
                             GL_DYNAMIC_STORAGE_BIT);
    }
    
    IndexBuffer::~IndexBuffer()
    {
        SGL_FUNCTION();
        glDeleteBuffers(1, &m_ID);
    }
    
    void IndexBuffer::Bind() const
    {
        SGL_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }
    
    void IndexBuffer::UnBind()
    {
        SGL_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

} // namespace sgl
