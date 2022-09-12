/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_INDEX_BUFFER_H_
#define SGL_OPENGL_INDEX_BUFFER_H_

#include <memory>
#include <cstdint>


namespace sgl
{
    // TODO template<typename T> typetraits to uint32_t, uint16_t, uint8_t
    class IndexBuffer
    {
    public:
        static std::shared_ptr<IndexBuffer> Create(const uint32_t* indices,
                                                   uint32_t indicesCount);
    public:
        IndexBuffer(const uint32_t* indices,
                    uint32_t indicesCount);
        ~IndexBuffer();

        void Bind() const;
        static void UnBind();

        uint32_t GetID() const { return m_ID; };
        inline uint32_t GetIndicesCount() const { return m_IndicesCount; };

        /**
         * @return Type of the indices in GL_enum equivalent value
         */
        uint32_t GetIndexType() const;

    private:
        uint32_t m_ID{ 0 };
        uint32_t m_IndicesCount{ 0 };
    };

} // namespace sgl

#endif // SGL_OPENGL_INDEX_BUFFER_H_
