/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "CubeMapTexture.h"


namespace sgl
{
    CubeMapTexture::CubeMapTexture(
        uint32_t faceWidth,
        uint32_t faceHeight,
        uint32_t faceChannels,
        const FacesData& facesData)
        : m_FaceWidth(faceWidth),
          m_FaceHeight(faceHeight),
          m_FaceFormat(faceChannels == 4 ? GL_RGBA : GL_RGB)
    {
        SGL_FUNCTION();
        CreateCubeMapTexture(facesData);
    }

    void CubeMapTexture::CreateCubeMapTexture(
        const FacesData& imagesData)
    {
        SGL_FUNCTION();
        CreateTexture();
        SetupStorage();
        SetFacesData(imagesData);
        SetTextureParams();
    }

    CubeMapTexture::~CubeMapTexture()
    {
        DeleteTexture();
    }

    void CubeMapTexture::Bind() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
    }

    void CubeMapTexture::UnBind() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void CubeMapTexture::CreateTexture()
    {
        SGL_FUNCTION();
        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_ID);
        SGL_ASSERT(m_ID > 0);
    }

    void CubeMapTexture::SetupStorage() const
    {
        SGL_FUNCTION();

        const uint32_t kFormat = m_FaceFormat == GL_RGB ? GL_RGB8
                                                        : GL_RGBA8;
        glTextureStorage2D(m_ID,
                           1,
                           kFormat,
                           m_FaceWidth,
                           m_FaceHeight);
    }

    void CubeMapTexture::SetFacesData(const FacesData& imagesData) const
    {
        SGL_FUNCTION();

        uint32_t face = 0;
        for (auto data : imagesData)
        {
            glTextureSubImage3D(m_ID,
                                0, // level,
                                0, // xoffset,
                                0, // yoffset,
                                face, // zoffset,
                                m_FaceWidth, // width,
                                m_FaceHeight, // height,
                                1, // depth,
                                m_FaceFormat, // format,
                                GL_UNSIGNED_BYTE, // type,
                                data);
            ++face;
        }
    }

    void CubeMapTexture::SetTextureParams() const
    {
        SGL_FUNCTION();

        int param = GL_LINEAR;
        glTextureParameteriv(m_ID, GL_TEXTURE_MIN_FILTER, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_MAG_FILTER, &param);
        param = GL_CLAMP_TO_EDGE;
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_S, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_T, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_R, &param);
    }

    void CubeMapTexture::DeleteTexture()
    {
        SGL_FUNCTION();
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
    }

} // namespace SGL
