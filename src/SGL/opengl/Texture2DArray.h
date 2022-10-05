/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_TEXTURE_2D_ARRAY_H_
#define SGL_OPENGL_TEXTURE_2D_ARRAY_H_

#include <vector>
#include <memory>


namespace sgl
{
    class Texture2DArray
    {
    public:
        struct TextureInfo 
        {
            int32_t width;
            int32_t height;
            uint32_t format;        ///< Sized texture format, e.g. GL_RGBA8
            uint32_t imageFormat;   ///< Image data format, e.g. GL_RGBA
            uint32_t imageDataType; ///< Image data type, e.g. GL_UNSIGNED_BYTE
            bool mipmaps;
        };

        static const uint32_t DEFAULT_WRAP_S, DEFAULT_WRAP_T;
        static const uint32_t DEFAULT_MIN_FILTER, 
                              DEFAULT_MIN_FILTER_MIPMAP, DEFAULT_MAG_FILTER;
    public:
        Texture2DArray();
        Texture2DArray(const TextureInfo& info,
                       const std::vector<const void*>& data);
        ~Texture2DArray();

        /** @brief Creates immutable data storage for all the textures
         * with the same properties, can be called only once.
         * @param info Properties of the textures (have the same properties)
         * @param data Image data of each texture
         */
        void SetDataImmutable(const TextureInfo& info,
                              const std::vector<const void*>& data);

        void Bind() const;
        static void UnBind();

        void SetWrap(uint32_t wrap_s, 
                     uint32_t wrap_t);
        void SetFiltering(uint32_t min_f,
                          uint32_t mag_f);
        void SetBorderColor(const glm::vec4& kColor) const;

    private:
        void Init(int32_t width, int32_t height, uint32_t format,
                  uint32_t imageFormat, uint32_t imageDataType, bool mipmaps);

        void CreateTexture();
        void DeleteTexture();

        void CreateStorageImmutable(const size_t kTextureCount) const;
        void UpdateData(const std::vector<const void*>& data) const;
        void GenMipMaps();

        void ApplyFiltering() const;
        void ApplyWrapping() const;

    private:
        uint32_t m_ID{ 0 };

        uint32_t m_Width{ 0 };
        uint32_t m_Height{ 0 };
        uint32_t m_MipLevels{ 1 };

        uint32_t m_Format{ 0 };
        uint32_t m_ImageFormat{ 0 };
        uint32_t m_ImageDataType{ 0 };

        uint32_t m_Wrap_S{ 0 };
        uint32_t m_Wrap_T{ 0 };
        uint32_t m_FilterMin{ 0 };
        uint32_t m_FilterMag{ 0 };
    };
    
} // namespace sgl


#endif // SGL_OPENGL_TEXTURE_2D_ARRAY_H_
