#ifndef SGL_OPENGL_INDEX_BUFFER_H_
#define SGL_OPENGL_INDEX_BUFFER_H_

#include <cstdint>


namespace sgl
{
    // TODO template<typename T> typetraits to uint32_t, uint16_t, uint8_t
    class IndexBuffer
    {
    public:
        IndexBuffer(const uint32_t* indices,
                    uint32_t indicesCount);
        ~IndexBuffer();

        void Bind() const;
        static void UnBind();

        uint32_t GetID() const { return m_ID; };
        uint32_t GetIndicesCount() const { return m_IndicesCount; };

    private:
        uint32_t m_ID{ 0 };
        uint32_t m_IndicesCount{ 0 };
    };

} // namespace sgl

#endif // SGL_OPENGL_INDEX_BUFFER_H_
