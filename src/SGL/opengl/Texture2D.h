/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_TEXTURE_2D_H_
#define SGL_OPENGL_TEXTURE_2D_H_

#include <memory>


namespace sgl
{
    class Texture2D
    {
    public:
        struct TextureInfo 
        {
            int32_t width;
            int32_t height;
            const void* data;
            uint32_t format;        ///< Sized texture format, e.g. GL_RGBA8
            uint32_t imageFormat;   ///< Image data format, e.g. GL_RGBA
            uint32_t imageDataType; ///< Image data type, e.g. GL_UNSIGNED_BYTE
            bool mipmaps;
        };

        static std::shared_ptr<Texture2D> Create();
        static std::shared_ptr<Texture2D> Create(const TextureInfo& info);

        static const uint32_t DEFAULT_WRAP_S, DEFAULT_WRAP_T;
        static const uint32_t DEFAULT_MIN_FILTER, 
                              DEFAULT_MIN_FILTER_MIPMAP, DEFAULT_MAG_FILTER;
    public:
        Texture2D();

        /** @brief Immutable data storage */
        Texture2D(const TextureInfo& info);
        ~Texture2D();

        void Bind() const;
        void BindUnit(uint32_t unit) const;

        static void UnBind();
        static void UnBindUnit(uint32_t unit);

        void SetDataImmutable(const TextureInfo& info);
        void UpdateData(const void* data) const;

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

        void CreateStorageImmutable() const;

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


#endif // SGL_OPENGL_TEXTURE_2D_H_
