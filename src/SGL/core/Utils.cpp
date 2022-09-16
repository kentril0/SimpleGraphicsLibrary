/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/core/Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


namespace sgl
{
    unsigned char* LoadImageData(const char* filename,
                                   int& outWidth,
                                   int& outHeight,
                                   int& outComponents,
                                   int requiredComponents)
    {
        SGL_FUNCTION();

        return stbi_load(filename,
                         &outWidth, &outHeight,
                         &outComponents, requiredComponents);
    }

    void FreeImageData(unsigned char* data)
    {
        SGL_FUNCTION();
        stbi_image_free(data);
    }

    STBData::STBData(int w, int h, int ch, unsigned char* p)
        : width(w),
          height(h),
          channels(ch),
          data(p)
    {
        SGL_FUNCTION();
    }

    STBData::~STBData()
    {
        SGL_FUNCTION();

        if (data != NULL)
        {
            FreeImageData(data);
        }
    }

    STBData LoadImage(const char* filename,
                      int requiredComponents)
    {
        SGL_FUNCTION();

        STBData data;
        data.data = LoadImageData(filename,
                                  data.width, data.height,
                                  data.channels, requiredComponents);
        return data;
    }
    
} // namespace sgl
