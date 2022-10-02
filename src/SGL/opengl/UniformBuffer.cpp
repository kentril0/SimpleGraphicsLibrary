/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/opengl/UniformBuffer.h"


namespace sgl
{
    UniformBuffer::UniformBuffer(uint32_t size, uint32_t binding)
    {
        SGL_FUNCTION();
        CreateBuffer();
        CreateStorageImmutable(size);

        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);
    }

    UniformBuffer::~UniformBuffer()
    {
        SGL_FUNCTION();
        DeleteBuffer();
    }

    void UniformBuffer::CreateBuffer()
    {
        SGL_FUNCTION();
        glCreateBuffers(1, &m_ID);
        SGL_ASSERT(m_ID > 0);
    }

    void UniformBuffer::DeleteBuffer()
    {
        SGL_FUNCTION();
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }

    void UniformBuffer::CreateStorageImmutable(uint32_t size) const
    {
        glNamedBufferStorage(m_ID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }

    void UniformBuffer::SetData(const void* data, uint32_t size,
                                uint32_t offset) const
    {
        glNamedBufferSubData(m_ID, offset, size, data);
    } 

    
} // namespace sgl
