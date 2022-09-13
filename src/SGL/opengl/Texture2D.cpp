
/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/opengl/Texture2D.h"


namespace sgl
{
    std::shared_ptr<Texture2D> Texture2D::Create()
    {
        return std::make_shared<Texture2D>();
    }

    std::shared_ptr<Texture2D> Texture2D::Create(
        uint32_t width, uint32_t height,
        const unsigned char* data,
        uint32_t format, uint32_t imageFormat, bool mipmaps)
    {
        return std::make_shared<Texture2D>(width, height, data, format,
                                           imageFormat, mipmaps);
    }

    const uint32_t Texture2D::DEFAULT_WRAP_S = GL_REPEAT;
    const uint32_t Texture2D::DEFAULT_WRAP_T = GL_REPEAT;
    const uint32_t Texture2D::DEFAULT_MIN_FILTER = GL_LINEAR;
    const uint32_t Texture2D::DEFAULT_MIN_FILTER_MIPMAP 
        = GL_LINEAR_MIPMAP_LINEAR;
    const uint32_t Texture2D::DEFAULT_MAG_FILTER = GL_LINEAR;

    // =========================================================================

    Texture2D::Texture2D()
    {
        SGL_FUNCTION();
        CreateTexture();
    }

    Texture2D::Texture2D(uint32_t width,
                         uint32_t height,
                         const unsigned char* data,
                         uint32_t format,
                         uint32_t imageFormat,
                         bool mipmaps)
    {
        SGL_FUNCTION();

        Init(width, height, format, imageFormat, mipmaps);
        CreateTexture();
        SetDataImmutable(data);
        GenMipMaps();

        ApplyFiltering();
    }

    Texture2D::~Texture2D()
    {
        SGL_FUNCTION();
        DeleteTexture();
    }

    void Texture2D::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    void Texture2D::BindUnit(uint32_t unit) const
    {
        glBindTextureUnit(unit, m_ID);
    }

    void Texture2D::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::UnBindUnit(uint32_t unit)
    {
        glBindTextureUnit(unit, 0);
    }

    void Texture2D::SetImage(uint32_t width, uint32_t height,
                             const unsigned char* data, uint32_t format,
                             uint32_t imageFormat, bool mipmaps)
    {
        SGL_FUNCTION();
        Init(width, height, format, imageFormat, mipmaps);

        SetDataImmutable(data);
        GenMipMaps();
        ApplyFiltering();
    }

    void Texture2D::CreateTexture()
    {
        SGL_FUNCTION();
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
        SGL_ASSERT(m_ID > 0);
    }

    void Texture2D::DeleteTexture()
    {
        SGL_FUNCTION();
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
    }

    void Texture2D::Init(uint32_t width, uint32_t height, uint32_t format,
                         uint32_t imageFormat, bool mipmaps)
    {
        SGL_FUNCTION();
        m_Width = width;
        m_Height = height;

        m_Format = format;
        m_ImageFormat = imageFormat;

        m_Wrap_S = Texture2D::DEFAULT_WRAP_S;
        m_Wrap_T = Texture2D::DEFAULT_WRAP_T;

        if (mipmaps)
        {
            m_MipLevels = std::log2(width);
            m_FilterMin = Texture2D::DEFAULT_MIN_FILTER_MIPMAP;
            m_FilterMag = Texture2D::DEFAULT_MAG_FILTER;
        }
        else
        {
            m_MipLevels = 1;
            m_FilterMin = Texture2D::DEFAULT_MIN_FILTER;
            m_FilterMag = Texture2D::DEFAULT_MAG_FILTER;
        }
    }

    void Texture2D::SetDataImmutable(const unsigned char* data) const
    {
        SGL_FUNCTION();

        // Specify IMMUTABLE storage for all levels of a 2D array texture
        glTextureStorage2D(m_ID,
                           // number of texture levels
                           m_MipLevels,
                           // sized format of stored data *RGBA8
                           m_Format,
                           // in texels
                           m_Width, m_Height);
        UpdateData(data);
    }

    void Texture2D::UpdateData(const unsigned char* data) const
    {
        SGL_FUNCTION();

        glTextureSubImage2D(m_ID,               // texture id
                            0,                  // level
                            // xoffset, yoffset in the texture array
                            0, 0,
                            // width, height of the subimage
                            m_Width, m_Height,
                            // format of the pixel data *RED, RGB, RGBA
                            m_ImageFormat,
                            // data type of the pixel data, *BYTE, FLOAT, INT
                            GL_UNSIGNED_BYTE,
                            // A pointer to the image data in memory
                            data);

    }

    void Texture2D::GenMipMaps()
    {
        SGL_FUNCTION();
        if (m_MipLevels <= 1)
            return;

        glGenerateTextureMipmap(m_ID);
    }

    void Texture2D::ApplyFiltering() const
    {
        SGL_FUNCTION();
        glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, m_FilterMin);
        glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, m_FilterMag);
    }
    
    void Texture2D::SetFiltering(uint32_t min_f, uint32_t mag_f)
    {
        SGL_FUNCTION();
        m_FilterMin = min_f;
        m_FilterMag = mag_f;

        ApplyFiltering();
    }

    void Texture2D::SetWrap(uint32_t wrap_s, uint32_t wrap_t)
    {
        SGL_FUNCTION();
        m_Wrap_S = wrap_s;
        m_Wrap_T = wrap_t;
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, wrap_s);
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, wrap_t);
    }

    void Texture2D::SetBorderColor(const glm::vec4& kColor) const
    {
        SGL_FUNCTION();
        glTextureParameterfv(m_ID, GL_TEXTURE_BORDER_COLOR,
                             glm::value_ptr(kColor));
    }
    
} // namespace sgl
