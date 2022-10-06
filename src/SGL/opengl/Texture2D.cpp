
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

    std::shared_ptr<Texture2D> Texture2D::Create(const TextureInfo& info)
    {
        return std::make_shared<Texture2D>(info);
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

    Texture2D::Texture2D(const TextureInfo& info)
        : Texture2D()
    {
        SetDataImmutable(info);
    }

    Texture2D::~Texture2D()
    {
        SGL_FUNCTION();
        DeleteTexture();
    }

    void Texture2D::SetDataImmutable(const TextureInfo& info)
    {
        SGL_FUNCTION();

        Init(info.width, info.height,
             info.format, info.imageFormat, info.imageDataType, info.mipmaps);

        CreateStorageImmutable();
        UpdateDataImmutable(info.data);

        GenMipMaps();
        ApplyFiltering();
        ApplyWrapping();
    }

    void Texture2D::SetData(const TextureInfo& info)
    {
        SGL_FUNCTION();

        Init(info.width, info.height,
             info.format, info.imageFormat, info.imageDataType, info.mipmaps);

        // glTexImage2D has only non-DSA variant, as per 4.5

        this->Bind();

        glTexImage2D(GL_TEXTURE_2D,
                     0,                 // Level
                     m_Format,          // Sized internal format
                     m_Width, m_Height, // Dimensions
                     0,                 // Border
                     m_ImageFormat,     // Image format
                     m_ImageDataType,   // Image datatype
                     info.data);        // Pointer to the image data

        GenMipMaps(); 
        ApplyFiltering();
        ApplyWrapping();

        this->UnBind();
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

    void Texture2D::Init(int32_t width, int32_t height, uint32_t format,
                         uint32_t imageFormat, uint32_t imageDataType,
                         bool mipmaps)
    {
        SGL_FUNCTION();
        m_Width = static_cast<uint32_t>(width);
        m_Height = static_cast<uint32_t>(height);

        m_Format = format;
        m_ImageFormat = imageFormat;
        m_ImageDataType = imageDataType;

        m_Wrap_S = Texture2D::DEFAULT_WRAP_S;
        m_Wrap_T = Texture2D::DEFAULT_WRAP_T;

        if (mipmaps)
        {
            m_MipLevels = static_cast<uint32_t>(
                std::floor( std::log2( std::max(width, height) ) )
            ) + 1;
            m_FilterMin = Texture2D::DEFAULT_MIN_FILTER_MIPMAP;
        }
        else
        {
            m_MipLevels = 1;
            m_FilterMin = Texture2D::DEFAULT_MIN_FILTER;
        }

        m_FilterMag = Texture2D::DEFAULT_MAG_FILTER;
    }

    void Texture2D::CreateStorageImmutable() const
    {
        SGL_FUNCTION();

        // Specify IMMUTABLE storage for all levels of a 2D texture
        glTextureStorage2D(m_ID,
                           // number of texture levels
                           m_MipLevels,
                           // sized format of stored data *RGBA8
                           m_Format,
                           // in texels
                           m_Width, m_Height);
    }

    void Texture2D::UpdateDataImmutable(const void* data) const
    {
        SGL_FUNCTION();

        glTextureSubImage2D(m_ID,               // texture id
                            0,                  // level
                            // xoffset, yoffset in the texture
                            0, 0,
                            // width, height of the subimage
                            m_Width, m_Height,
                            // format of the pixel data *RED, RGB, RGBA
                            m_ImageFormat,
                            // data type of the pixel data, *BYTE, FLOAT, INT
                            m_ImageDataType,
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

    void Texture2D::ApplyWrapping() const
    {
        SGL_FUNCTION();
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, m_Wrap_S);
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, m_Wrap_T);
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

        ApplyWrapping();
    }

    void Texture2D::SetBorderColor(const glm::vec4& kColor) const
    {
        SGL_FUNCTION();
        glTextureParameterfv(m_ID, GL_TEXTURE_BORDER_COLOR,
                             glm::value_ptr(kColor));
    }
    
} // namespace sgl
