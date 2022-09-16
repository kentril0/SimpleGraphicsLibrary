/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include <SGL/opengl/BufferLayout.h>

#include <sstream>

#define FLOAT_BYTES ( sizeof(float) )
#define INT32_BYTES ( sizeof(int32_t) )
#define UINT8_BYTES ( sizeof(uint8_t) )


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

        CalculateStride();  // must be called before offsets are computed
        CalculateElementOffsets();
    }

    void BufferLayout::CalculateElementOffsets()
    {
        SGL_FUNCTION();

        int64_t offset = 0;
        for (auto& element : m_Elements)
        {
            if (element.offset == 0)
            {
                if (element.relOffset == 0)
                {
                    element.offset = offset;
                    offset += element.size;
                }
                else    // Part of the same 'structure', different relOffset
                {
                    offset += element.size;
                }
            }
            else    // Possibly deinterleaved buffer
            {
                offset = element.offset + element.size;
            }
        }
    } 

    void BufferLayout::CalculateStride()
    {
        SGL_FUNCTION();

        uint32_t i = 0;
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            // Is deinterleaved
            if (i > 0 && element.offset != 0)
                break;

            m_Stride += element.size;
            ++i;
        }
    }

    void BufferLayout::DebugPrint() const
    {
    #ifdef SGL_DEBUG
        SGL_LOG_INFO("BufferLayout info:\n Elements total: {}, Stride {}",
                     m_Elements.size(), m_Stride);

        uint32_t ctr = 0;
        for (const auto& e : m_Elements)
        {
            SGL_LOG_INFO(" Element {}: {}", ctr++, e.ToString());
        }
    #endif
    }

    // =========================================================================

    BufferElement::BufferElement(ElementType type, const char* desc,
                                 int32_t offset, int32_t relativeOffset,
                                 bool normalized)
        : type(type),
          size(ElementTypeSize()),
          offset(offset),
          relOffset(relativeOffset),
          normalized(normalized)
    {
        (void)desc;
    }

    uint32_t BufferElement::ElementTypeSize() const
    {
        switch(type)
        {
            case ElementType::Float:     return FLOAT_BYTES;
            case ElementType::Float2:    return FLOAT_BYTES * 2;
            case ElementType::Float3:    return FLOAT_BYTES * 3;
            case ElementType::Float4:    return FLOAT_BYTES * 4;
            case ElementType::Mat3:      return FLOAT_BYTES * 3 * 3;
            case ElementType::Mat4:      return FLOAT_BYTES * 4 * 4;
            case ElementType::Int:       return INT32_BYTES;
            case ElementType::Int2:      return INT32_BYTES * 2;
            case ElementType::Int3:      return INT32_BYTES * 3;
            case ElementType::Int4:      return INT32_BYTES * 4;
            case ElementType::UInt8:     return UINT8_BYTES;
            case ElementType::UInt8_2:   return UINT8_BYTES * 2;
            case ElementType::UInt8_3:   return UINT8_BYTES * 3;
            case ElementType::UInt:      return INT32_BYTES * 2;
            case ElementType::UInt2:     return INT32_BYTES * 2;
            case ElementType::UInt3:     return INT32_BYTES * 3;
            case ElementType::Bool:      return UINT8_BYTES;
        }
        SGL_ASSERT_MSG(false, "Unknown buffer element data type: {}",
                       ElementTypeToString(type) );
        return 0;
    }

    uint32_t BufferElement::ComponentCount() const
    {
        switch(type)
        {
            case ElementType::Float:     return 1;
            case ElementType::Float2:    return 2;
            case ElementType::Float3:    return 3;
            case ElementType::Float4:    return 4;
            case ElementType::Mat3:      return 3;  // 3 * Float3
            case ElementType::Mat4:      return 4;  // 4 * Float4
            case ElementType::Int:       return 1;
            case ElementType::Int2:      return 2;
            case ElementType::Int3:      return 3;
            case ElementType::Int4:      return 4;
            case ElementType::UInt8:     return 1;
            case ElementType::UInt8_2:   return 2;
            case ElementType::UInt8_3:   return 3;
            case ElementType::UInt:      return 1;
            case ElementType::UInt2:     return 2;
            case ElementType::UInt3:     return 3;
            case ElementType::Bool:      return 1;
        }
        SGL_ASSERT_MSG(false, "Unknown buffer element data type: {}",
                       ElementTypeToString(type));
        return 0;
    }

    std::string BufferElement::ToString() const
    {
        std::stringstream ss;
        ss << "Type: " << ElementTypeToString(type)
           << ", Size: " << size
           << ", Offset: " << offset
           << ", RelOffset: " << relOffset
           << ", Normalized: " << normalized;
        return ss.str();
    }

    // =========================================================================

    const char* ElementTypeToString(ElementType type)
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

} // namespace sgl
