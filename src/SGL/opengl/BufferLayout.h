#ifndef SGL_OPENGL_BUFFER_LAYOUT_H_
#define SGL_OPENGL_BUFFER_LAYOUT_H_

#include <cstdint>
#include <vector>


namespace sgl
{
    enum class ElementType 
    {
        Bool = 0,
        UInt8, UInt8_2, UInt8_3, 
        Int, Int2, Int3, Int4,
        UInt, UInt2, UInt3,
        Float, Float2, Float3, Float4,
        Mat3, Mat4
    };

    static constexpr auto FLOAT_BYTES = sizeof(float);
    static constexpr auto INT32_BYTES = sizeof(int32_t);
    static constexpr auto UINT8_BYTES = sizeof(uint8_t);

    struct BufferElement
    {
        ElementType type;
        uint32_t size;
        int32_t offset;
        bool normalized;

        BufferElement() = default;

        /** 
         * @param desc Only used as a self-description
         * @param offset 
         * @param normalized If true, will be converted to floating-point to
         *  [0,1] for unsigned or [-1,1] for signed types.
         */
        BufferElement(ElementType type, 
                      const char* desc, 
                      int32_t offset = 0,
                      bool normalized = false)
          : type(type), size(ElementTypeSize()), offset(offset),
            normalized(normalized)
        { 
            (void)desc;
        }

        constexpr uint32_t ElementTypeSize() const
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
            //SGL_ASSERT_MSG(false, "Unknown buffer element data type: {}", type);
            return 0;
        }

        /** @return Number of components of the element type */
        constexpr uint32_t ComponentCount() const
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
            //SGL_ASSERT_MSG(false, "Unknown buffer element data type: {}", type);
            return 0;        
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& elements);
        
        const std::vector<BufferElement>& GetElements() const {
            return m_Elements;
        }
        /** @return Stride - size in bytes - between the elements */
        uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() {
            return m_Elements.begin();
        }
        std::vector<BufferElement>::iterator end() {
            return m_Elements.end();
        }

        std::vector<BufferElement>::const_iterator begin() const {
            return m_Elements.begin();
        }
        std::vector<BufferElement>::const_iterator end() const {
            return m_Elements.end();
        }
    private:
        void CalculateElementOffsets();
        void CalculateStride();

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride{ 0 };
    };

} // namespace sgl


#endif // SGL_OPENGL_BUFFER_LAYOUT_H_
