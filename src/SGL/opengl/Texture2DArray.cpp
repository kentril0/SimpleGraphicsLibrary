/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/opengl/Texture2DArray.h"


namespace sgl
{
    const uint32_t Texture2DArray::DEFAULT_WRAP_S = GL_REPEAT;
    const uint32_t Texture2DArray::DEFAULT_WRAP_T = GL_REPEAT;
    const uint32_t Texture2DArray::DEFAULT_MIN_FILTER = GL_LINEAR;
    const uint32_t Texture2DArray::DEFAULT_MIN_FILTER_MIPMAP 
        = GL_LINEAR_MIPMAP_LINEAR;
    const uint32_t Texture2DArray::DEFAULT_MAG_FILTER = GL_LINEAR;

    Texture2DArray::Texture2DArray()
    {
        SGL_FUNCTION();
        CreateTexture();
    }

    Texture2DArray::Texture2DArray(const TextureInfo& info,
                                   const std::vector<const void*>& data)
        : Texture2DArray()
    {
        SGL_FUNCTION();
        SetDataImmutable(info, data);
    }
    
    Texture2DArray::~Texture2DArray()
    {
        SGL_FUNCTION();
        DeleteTexture();
    }

    void Texture2DArray::SetDataImmutable(const TextureInfo& info,
                                          const std::vector<const void*>& data)
    {
        SGL_FUNCTION();

        Init(info.width, info.height,
             info.format, info.imageFormat, info.imageDataType, info.mipmaps);

        CreateStorageImmutable(data.size());
        UpdateData(data);

        GenMipMaps();
        ApplyFiltering();
        ApplyWrapping();
    }

    void Texture2DArray::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
    }

    void Texture2DArray::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void Texture2DArray::CreateTexture()
    {
        SGL_FUNCTION();
        glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_ID);
        SGL_ASSERT(m_ID > 0);
    }

    void Texture2DArray::DeleteTexture()
    {
        SGL_FUNCTION();
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
    }

    void Texture2DArray::Init(int32_t width, int32_t height, uint32_t format,
                              uint32_t imageFormat, uint32_t imageDataType,
                              bool mipmaps)
    {
        SGL_FUNCTION();
        m_Width = static_cast<uint32_t>(width);
        m_Height = static_cast<uint32_t>(height);

        m_Format = format;
        m_ImageFormat = imageFormat;
        m_ImageDataType = imageDataType;

        m_Wrap_S = Texture2DArray::DEFAULT_WRAP_S;
        m_Wrap_T = Texture2DArray::DEFAULT_WRAP_T;

        if (mipmaps)
        {
            m_MipLevels = static_cast<uint32_t>(
                std::floor( std::log2( std::max(width, height) ) )
            ) + 1;
            m_FilterMin = Texture2DArray::DEFAULT_MIN_FILTER_MIPMAP;
        }
        else
        {
            m_MipLevels = 1;
            m_FilterMin = Texture2DArray::DEFAULT_MIN_FILTER;
        }

        m_FilterMag = Texture2DArray::DEFAULT_MAG_FILTER;
    }

    void Texture2DArray::CreateStorageImmutable(const size_t kTextureCount) const
    {
        SGL_FUNCTION();

        glTextureStorage3D(m_ID,
                           m_MipLevels,
                           m_Format,
                           m_Width,
                           m_Height,
                           kTextureCount);
    }

    void Texture2DArray::UpdateData(const std::vector<const void*>& data) const
    {
        SGL_FUNCTION();

        for (uint32_t i = 0; i < data.size(); ++i)
        {
            glTextureSubImage3D(m_ID,
                                0, // mipmap_level,
                                0, // offset.x,
                                0, // offset.y,
                                i, //layer,
                                m_Width, //width,
                                m_Height, //height,
                                1,
                                m_ImageFormat,
                                m_ImageDataType,
                                data[i]);
        }
    }

    void Texture2DArray::GenMipMaps()
    {
        SGL_FUNCTION();
        if (m_MipLevels <= 1)
            return;

        glGenerateTextureMipmap(m_ID);
    }

    void Texture2DArray::ApplyFiltering() const
    {
        SGL_FUNCTION();
        glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, m_FilterMin);
        glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, m_FilterMag);
    }

    void Texture2DArray::ApplyWrapping() const
    {
        SGL_FUNCTION();
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, m_Wrap_S);
        glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, m_Wrap_T);
    }
    
    void Texture2DArray::SetFiltering(uint32_t min_f, uint32_t mag_f)
    {
        SGL_FUNCTION();
        m_FilterMin = min_f;
        m_FilterMag = mag_f;

        ApplyFiltering();
    }

    void Texture2DArray::SetWrap(uint32_t wrap_s, uint32_t wrap_t)
    {
        SGL_FUNCTION();
        m_Wrap_S = wrap_s;
        m_Wrap_T = wrap_t;

        ApplyWrapping();
    }

    void Texture2DArray::SetBorderColor(const glm::vec4& kColor) const
    {
        SGL_FUNCTION();
        glTextureParameterfv(m_ID, GL_TEXTURE_BORDER_COLOR,
                             glm::value_ptr(kColor));
    }

} // namespace sgl
