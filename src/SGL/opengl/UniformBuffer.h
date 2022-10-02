/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_UNIFORM_BUFFER_H_
#define SGL_OPENGL_UNIFORM_BUFFER_H_

#include <memory>


namespace sgl
{
    class UniformBuffer
    {
    public:
        /**
         * Creates uniform buffer object with immutable storage 
         * @param size Size in bytes
         * @param binding BInding point
         */
        UniformBuffer(uint32_t size,
                      uint32_t binding);
        ~UniformBuffer();

        void SetData(const void* data,
                     uint32_t size,
                     uint32_t offset = 0) const;

    private:
        void CreateBuffer();
        void DeleteBuffer();
        void CreateStorageImmutable(uint32_t size) const;

    private:
        uint32_t m_ID{ 0 };
    };
    
} // namespace sgl


#endif // SGL_OPENGL_UNIFORM_BUFFER_H_
