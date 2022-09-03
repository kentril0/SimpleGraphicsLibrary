#include <SGL/opengl/VertexArray.h>

#include <glad/glad.h>

#include <SGL/core/Log.h>
#include <SGL/core/Assert.h>
#include <SGL/opengl/VertexBuffer.h>
#include <SGL/opengl/BufferLayout.h>


namespace sgl
{
    static constexpr GLenum ElementToShaderType(ElementType type)
    {
        switch(type)
        {
            case ElementType::Float:     return GL_FLOAT;
            case ElementType::Float2:    return GL_FLOAT;
            case ElementType::Float3:    return GL_FLOAT;
            case ElementType::Float4:    return GL_FLOAT;
            case ElementType::Mat3:      return GL_FLOAT;
            case ElementType::Mat4:      return GL_FLOAT;
            case ElementType::Int:       return GL_INT;
            case ElementType::Int2:      return GL_INT;
            case ElementType::Int3:      return GL_INT;
            case ElementType::Int4:      return GL_INT;
            case ElementType::UInt8:     return GL_UNSIGNED_BYTE;
            case ElementType::UInt8_2:   return GL_UNSIGNED_BYTE;
            case ElementType::UInt8_3:   return GL_UNSIGNED_BYTE;
            case ElementType::UInt:      return GL_UNSIGNED_INT;
            case ElementType::UInt2:     return GL_UNSIGNED_INT;
            case ElementType::UInt3:     return GL_UNSIGNED_INT;
            case ElementType::Bool:      return GL_BYTE;
        }
        SGL_ASSERT_MSG(false, "Unknown buffer element data type: {}", type);
        return 0;
    }

    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<VertexArray>();
    }

    VertexArray::VertexArray()
    {
        SGL_FUNCTION();
        CreateVertexArray();
    }

    VertexArray::~VertexArray()
    {
        SGL_FUNCTION();
        DeleteVertexArray();
    }

    void VertexArray::CreateVertexArray()
    {
        SGL_FUNCTION();
        glCreateVertexArrays(1, &m_ID);
    }

    void VertexArray::DeleteVertexArray()
    {
        SGL_FUNCTION();
        glDeleteVertexArrays(1, &m_ID);
        m_ID = 0;
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo,
                                      bool instanced)
    {
        SGL_FUNCTION();
        const auto& layout = vbo->GetLayout();

        const bool kVBOHasFormat = layout.GetElements().size() > 0;
        SGL_ASSERT(kVBOHasFormat);

        const uint32_t kPerInstance = 1, kPerVertex = 0;
        const uint32_t kDivisor = instanced ? kPerInstance : kPerVertex;

        for (const auto& e : layout)
        {
            switch(e.type)
            {
                case ElementType::Float: case ElementType::Float2:
                case ElementType::Float3: case ElementType::Float4:
                case ElementType::Int: case ElementType::Int2:  
                case ElementType::Int3: case ElementType::Int4:  
                case ElementType::UInt8: case ElementType::UInt8_2:
                case ElementType::UInt8_3:
                case ElementType::UInt: case ElementType::UInt2: 
                case ElementType::UInt3: 
                case ElementType::Bool:
                {
                    SpecifyVertexAttribute(vbo->GetID(), layout.GetStride(), e,
                                           kDivisor);
                /*
                    // Attach a vertex attribute of the VBO to an attrib index
                    const int32_t kFirstElementOffset = 0;
                    const uint32_t kAttribIndex = m_BindingIndex;
                    glVertexArrayVertexBuffer(m_ID,
                                              kAttribIndex, vbo->GetID(),
                                              kFirstElementOffset,
                                              layout.GetStride());

                    // Enable the vertex attribute array in the VBO
                    glEnableVertexArrayAttrib(m_ID, kAttribIndex);

                    // Specify organization of arrays of vertex attribs
                    glVertexArrayAttribFormat(m_ID, kAttribIndex,
                        e.ComponentCount(),   // values per vertex (and ordering)
                        ElementToShaderType(e.type),    // GL data type of values
                        e.normalized ? GL_TRUE : GL_FALSE,
                        e.offset);  // offset of the 1st elem relative to the
                        // start of the vertex buffer binding this attribute
                        // fetches from

                    // Associate the vertex attrib. idx with the VBO binding idx
                    glVertexArrayAttribBinding(m_ID, kAttribIndex, 
                                               m_BindingIndex);

                    glVertexArrayBindingDivisor(m_ID, m_BindingIndex, kDivisor);

                    ++m_BindingIndex;
                */
                    break;
                }
                case ElementType::Mat3:  
                case ElementType::Mat4:  
                {
                    const uint32_t kComponentCount = e.ComponentCount();
                    for (uint32_t i = 0; i < kComponentCount; ++i)
                    {
                        SpecifyVertexAttribute(vbo->GetID(), layout.GetStride(), e,
                                               kPerInstance,   // GLSL limitation
                                               i * kComponentCount * sizeof(float));
                        
                        /*
                        const int32_t kFirstElementOffset = 0;
                        const uint32_t kAttribIndex = m_BindingIndex;
                        glVertexArrayVertexBuffer(m_ID,
                                                  kAttribIndex, vbo->GetID(),
                                                  kFirstElementOffset, 
                                                  layout.GetStride());

                        glEnableVertexArrayAttrib(m_ID, kAttribIndex);

                        glVertexArrayAttribFormat(m_ID, kAttribIndex, 
                                                  kComponentCount,
                                                  ElementToShaderType(e.type),
                                                  e.normalized ? GL_TRUE : GL_FALSE, 
                                                  e.offset + 
                                                    i * kComponentCount * sizeof(float));

                        glVertexArrayAttribBinding(m_ID, kAttribIndex, 
                                                   m_BindingIndex);
                    
                        // Per instance (GLSL vec4 limitation)
                        glVertexAttribDivisor(kAttribIndex, 1);

                        ++m_BindingIndex;
                        */
                    }
                    break;
                }
                default:
                    SGL_ASSERT_MSG(false, "Unknown buffer element data type: "
                                          "{}", e.type);
            }
        }

        m_VertexBuffers.push_back(vbo);
    }

    void VertexArray::SpecifyVertexAttribute(const uint32_t kVboID,
        const uint32_t kStride, const BufferElement& e, const uint32_t kDivisor,
        const int32_t kComponentOffset)
    {
        SGL_FUNCTION();

        // Attach a vertex attribute of the VBO to an attrib index
        const int32_t kFirstElementOffset = 0;
        const uint32_t kAttribIndex = m_BindingIndex;

        glVertexArrayVertexBuffer(m_ID,
                                  kAttribIndex, kVboID,
                                  kFirstElementOffset,
                                  kStride);

        // Enable the vertex attribute array in the VBO
        glEnableVertexArrayAttrib(m_ID, kAttribIndex);

        // Specify organization of arrays of vertex attribs
        glVertexArrayAttribFormat(m_ID, kAttribIndex,
            e.ComponentCount(),             // values per vertex (and ordering)
            ElementToShaderType(e.type),    // GL data type of values
            e.normalized ? GL_TRUE : GL_FALSE,
            e.offset + kComponentOffset);   // offset of the 1st element 
            //  relative to the start of the vertex buffer binding this
            //  attribute fetches from

        // Associate the vertex attrib. idx with the VBO binding idx
        glVertexArrayAttribBinding(m_ID, kAttribIndex, 
                                   m_BindingIndex);

        glVertexArrayBindingDivisor(m_ID, m_BindingIndex, kDivisor);

        ++m_BindingIndex;
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo)
    {
        SGL_FUNCTION();

        glVertexArrayElementBuffer( m_ID, ibo->GetID() );
        m_IndexBuffer = ibo;
    }

    void VertexArray::Bind() const
    {
        SGL_FUNCTION();
        glBindVertexArray(m_ID);
    }

    void VertexArray::UnBind()
    {
        SGL_FUNCTION();
        glBindVertexArray(0);
    }

} // namespace sgl
