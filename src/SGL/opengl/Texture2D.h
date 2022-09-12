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
        static std::shared_ptr<Texture2D> Create();
        static std::shared_ptr<Texture2D> Create(uint32_t width,
                                                 uint32_t height,
                                                 const unsigned char* data,
                                                 uint32_t format,
                                                 uint32_t imageFormat,
                                                 bool mipmaps = false);

        static const uint32_t DEFAULT_WRAP_S, DEFAULT_WRAP_T;
        static const uint32_t DEFAULT_MIN_FILTER, 
                              DEFAULT_MIN_FILTER_MIPMAP, DEFAULT_MAG_FILTER;
    public:
        Texture2D();

        /** @brief Immutable */
        Texture2D(uint32_t width,
                  uint32_t height,
                  const unsigned char* data,
                  uint32_t format,
                  uint32_t imageFormat,
                  bool mipmaps = false);

        ~Texture2D();

        void Bind() const;
        void BindUnit(uint32_t unit) const;

        static void UnBind();
        static void UnBindUnit(uint32_t unit);

        /** @brief Immutable */
        void SetImage(uint32_t width,
                      uint32_t height,
                      const unsigned char* data,
                      uint32_t format,
                      uint32_t imageFormat,
                      bool mipmaps = false);
        
        void UpdateData(const unsigned char* data) const;

        void SetWrap(uint32_t wrap_s, 
                     uint32_t wrap_t);

        void SetFiltering(uint32_t min_f,
                          uint32_t mag_f);
        void SetBorderColor(const glm::vec4& kColor) const;

    private:
        void Init(uint32_t width, uint32_t height, uint32_t format,
                  uint32_t imageFormat, bool mipmaps);

        void CreateTexture();
        void DeleteTexture();

        void SetDataImmutable(const unsigned char* data) const;

        void GenMipMaps();

        void ApplyFiltering() const;

    private:
        uint32_t m_ID{ 0 };

        uint32_t m_Width{ 0 };
        uint32_t m_Height{ 0 };
        uint32_t m_MipLevels{ 1 };

        uint32_t m_Format{ 0 };
        uint32_t m_ImageFormat{ 0 };

        uint32_t m_Wrap_S{ 0 };
        uint32_t m_Wrap_T{ 0 };
        uint32_t m_FilterMin{ 0 };
        uint32_t m_FilterMag{ 0 };
    };
    
} // namespace sgl


#endif // SGL_OPENGL_TEXTURE_2D_H_
