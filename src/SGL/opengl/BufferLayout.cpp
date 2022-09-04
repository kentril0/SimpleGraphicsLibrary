#include <SGL/opengl/BufferLayout.h>

#include <cstdint>
#include <sstream>

#include <SGL/core/Base.h>
#include <SGL/core/Log.h>
#include <SGL/core/Assert.h>

#define FLOAT_BYTES (sizeof(float))
#define INT32_BYTES (sizeof(int32_t))
#define UINT8_BYTES (sizeof(uint8_t))


namespace sgl
{
    BufferLayout::BufferLayout()
    {
        SGL_FUNCTION();
    }

    BufferLayout::BufferLayout(
        const std::initializer_list<BufferElement>& elements)
        : m_Elements(elements)
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

    static const char* ElementTypeToString(ElementType type)
    {
        switch(type)
        {
            case ElementType::Float:     return "Float";
            case ElementType::Float2:    return "Float2";
            case ElementType::Float3:    return "Float3";
            case ElementType::Float4:    return "Float4";
            case ElementType::Mat3:      return "Mat3" ;
            case ElementType::Mat4:      return "Mat4" ;
            case ElementType::Int:       return "Int"  ;
            case ElementType::Int2:      return "Int2" ;
            case ElementType::Int3:      return "Int3" ;
            case ElementType::Int4:      return "Int4" ;
            case ElementType::UInt8:     return "Uint8";
            case ElementType::UInt8_2:   return "Uint8_2";
            case ElementType::UInt8_3:   return "Uint8_3";
            case ElementType::UInt:      return "Uint" ;
            case ElementType::UInt2:     return "UInt2";
            case ElementType::UInt3:     return "UInt3";
            case ElementType::Bool:      return "Bool" ;
        }
        SGL_ASSERT_MSG(false, "Unknown buffer element data type");
        return "";
    }

    std::string BufferElement::ToString() const
    {
        std::stringstream ss;
        ss << "Type: " << ElementTypeToString(type)
           << ", Size: " << size
           << ", Offset: " << offset
           << ", Normalized: " << normalized;
        return ss.str();
    }

    void BufferLayout::DebugPrint() const
    {
    #ifdef SGL_DEBUG
        SGL_LOG_INFO("BufferLayout info:");

        uint32_t ctr = 0;
        for (const auto& e : m_Elements)
        {
            SGL_LOG_INFO("Element {}: {}", ctr++, e.ToString());
        }
    #endif
    }

} // namespace sgl
