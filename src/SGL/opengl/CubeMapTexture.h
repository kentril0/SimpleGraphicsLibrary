/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_CUBE_MAP_TEXTURE_H_
#define SGL_OPENGL_CUBE_MAP_TEXTURE_H_

#include <array>
#include <cstdint>


namespace sgl
{
    class CubeMapTexture
    {
    public: 
        static constexpr uint32_t CubeFaceCount = 6;

        typedef std::array<
            unsigned char*, CubeMapTexture::CubeFaceCount
        > FacesData;

    public:
        CubeMapTexture(uint32_t faceWidth,
                       uint32_t faceHeight,
                       uint32_t faceChannels,
                       const FacesData& facesData);
        ~CubeMapTexture();

        void Bind() const;
        void UnBind() const;

    private:
        void CreateCubeMapTexture(const FacesData& imagesData);
        void SetupStorage() const;
        void SetFacesData(const FacesData& imagesData) const;
        void DeleteTexture();

        void SetTextureParams() const;
        void CreateTexture();

    private:
        uint32_t m_ID{ 0 };

        uint32_t m_FaceWidth{ 0 };
        uint32_t m_FaceHeight{ 0 };
        uint32_t m_FaceFormat{ 0 };
    };

} // namespace sgl


#endif // SGL_OPENGL_CUBE_MAP_TEXTURE_H_
