#include <SGL/opengl/BufferLayout.h>

#include <cstdint>

#include <SGL/core/Log.h>
#include <SGL/core/Assert.h>

#define FLOAT_BYTES (sizeof(float))
#define INT32_BYTES (sizeof(int32_t))
#define UINT8_BYTES (sizeof(uint8_t))


namespace sgl
{
    BufferLayout::BufferLayout(
        const std::initializer_list<BufferElement>& elements)
    {
        SGL_FUNCTION();
        CalculateElementOffsets();
        CalculateStride();
    }

    void BufferLayout::CalculateElementOffsets()
    {
        SGL_FUNCTION();
        int64_t offset = 0;
        for (auto& element : m_Elements)
        {
            element.offset = offset;
            offset += element.size;
        }
    } 

    void BufferLayout::CalculateStride()
    {
        SGL_FUNCTION();
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            m_Stride += element.size;
        }
    }

} // namespace sgl
