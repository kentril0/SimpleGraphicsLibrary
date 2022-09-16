/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_BUFFER_LAYOUT_H_
#define SGL_OPENGL_BUFFER_LAYOUT_H_

#include <cstdint>
#include <vector>
#include <string>


namespace sgl
{
    struct BufferElement;

    class BufferLayout
    {
    public:
        BufferLayout();
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

        void DebugPrint() const;

    private:
        void CalculateElementOffsets();
        void CalculateStride();

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride{ 0 };
    };

    enum class ElementType 
    {
        Bool = 0,
        UInt8, UInt8_2, UInt8_3, 
        Int, Int2, Int3, Int4,
        UInt, UInt2, UInt3,
        Float, Float2, Float3, Float4,
        Mat3, Mat4
    };

    const char* ElementTypeToString(ElementType type);

    struct BufferElement
    {
        ElementType type;
        uint32_t size;
        int32_t offset;
        int32_t relOffset;
        bool normalized;

        BufferElement() = default;

        /** 
         * @param type Type of the element as an attribute.
         * @param desc Used only as a note to yourself.
         * @param offset Starting byte of the element in the buffer.
         * @param relativeOffset Starting byte inside a structure the element is
         *  part of.
         * @param normalized If true, will be converted to floating-point to
         *  [0,1] for unsigned or [-1,1] for signed types.
         */
        BufferElement(ElementType type,
                      const char* desc,
                      int32_t offset = 0,
                      int32_t relativeOffset = 0,
                      bool normalized = false);

        uint32_t ElementTypeSize() const;

        /** @return Number of components of the element type */
        uint32_t ComponentCount() const;

        std::string ToString() const;
    };

} // namespace sgl


#endif // SGL_OPENGL_BUFFER_LAYOUT_H_
