#ifndef SGL_OPENGL_VERTEX_BUFFER_H_
#define SGL_OPENGL_VERTEX_BUFFER_H_

#include <memory>
#include <array>
#include <vector>


namespace sgl
{
    class VertexBuffer
    {
    public:
        /**
         * @brief Creates a vertex buffer with undefined allocated data store,
         *  expects the data to be updated later
         * @param size Reserved size in bytes
         * @param immutable If true, then the buffer store cannot be 
         *  re-allocated, and cannot be deallocated until deleted.
         *  The data may still be updated later, regardless of mutability.
         */
        static std::shared_ptr<VertexBuffer> Create(uint32_t size,
                                                    bool immutable = false);
        /**
         * @brief Creates a vertex buffer with allocated pre-defined data,
         *  expects the data to be static
         * @param size Size of the data in bytes
         * @param immutable If true, then the buffer store cannot be 
         *  re-allocated, and cannot be deallocated until deleted.
         *  The data may still be updated later, regardless of mutability.
         */
        static std::shared_ptr<VertexBuffer> Create(const void* data,
                                                    uint32_t size,
                                                    bool immutable = false);
    public:
        /**
         * @brief Creates a vertex buffer with undefined allocated data store,
         *  expects the data to be updated later
         * @param size Reserved size in bytes
         * @param immutable If true, then the buffer store cannot be 
         *  re-allocated, and cannot be deallocated until deleted.
         *  The data may still be updated later, regardless of mutability.
         */
        VertexBuffer(uint32_t size,
                     bool immutable = false);
        /**
         * @brief Creates a vertex buffer with allocated pre-defined data,
         *  expects the data to be static
         * @param size Size of the data in bytes
         * @param immutable If true, then the buffer store cannot be 
         *  re-allocated, and cannot be deallocated until deleted.
         *  The data may still be updated later, regardless of mutability.
         */
        VertexBuffer(const void* data,
                     uint32_t size,
                     bool immutable = false);

        ~VertexBuffer();

        void Bind() const;
        static void UnBind();

        void UpdateData(const void* data,
                        uint32_t size,
                        int32_t offset = 0) const;

    private:
        void CreateBuffer();
        void DeleteBuffer();

        void AllocateData(const void* data,
                          uint32_t size,
                          bool immutable) const;

    private:
        uint32_t m_ID{ 0 };
    };

} // namespace sgl


#endif // SGL_OPENGL_VERTEX_BUFFER_H_
