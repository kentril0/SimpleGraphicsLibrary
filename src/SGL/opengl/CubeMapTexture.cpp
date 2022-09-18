#include "CubeMapTexture.h"

#include <SGL/SGL.h>


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

    void CubeMapTexture::CreateCubeMapTexture(
        const FacesData& imagesData)
    {
        SGL_FUNCTION();

    #ifndef SGL_GL_33
        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_ID);
        SGL_ASSERT(m_ID > 0);

        glTextureStorage2D(m_ID,
                           1,
                           GL_RGB8,
                           m_FaceWidth,
                           m_FaceHeight);

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
    #else
        glGenTextures(1, &m_ID);
        this->Bind();
        SGL_ASSERT(m_ID > 0);

        uint32_t i = 0;
        for (auto data : imagesData)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, 
                         m_FaceFormat,
                         m_FaceWidth, m_FaceHeight, 
                         0, m_FaceFormat,
                         GL_UNSIGNED_BYTE, data);
            ++i;
        }
    #endif

        //// Set filtering, wrapping
    #ifndef SGL_GL_33
        int param = GL_LINEAR;
        glTextureParameteriv(m_ID, GL_TEXTURE_MIN_FILTER, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_MAG_FILTER, &param);
        param = GL_CLAMP_TO_EDGE;
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_S, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_T, &param);
        glTextureParameteriv(m_ID, GL_TEXTURE_WRAP_R, &param);
    #else
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        this->UnBind();
    #endif
    }

    void CubeMapTexture::DeleteTexture()
    {
        SGL_FUNCTION();
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
    }
}