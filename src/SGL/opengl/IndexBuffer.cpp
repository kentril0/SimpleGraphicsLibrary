/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include <SGL/opengl/IndexBuffer.h>


namespace sgl
{
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices,
                                                     uint32_t indicesCount)
    {
        return std::make_shared<IndexBuffer>(indices, indicesCount);
    }

    // =========================================================================

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

    uint32_t IndexBuffer::GetIndexType() const
    {
        return GL_UNSIGNED_INT;
    }

} // namespace sgl
