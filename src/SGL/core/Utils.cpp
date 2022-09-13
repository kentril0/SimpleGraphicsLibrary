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

        int w = 0, h = 0, n = 0;
        auto p = stbi_load(filename,
                           &w, &h,
                           &n, requiredComponents);
        outWidth = w;
        outHeight = h;
        outComponents = n;

        return p;
    }

    void FreeImageData(unsigned char* data)
    {
        SGL_FUNCTION();
        stbi_image_free(data);
    }

    STBData::STBData(unsigned char* p)
        : data(p)
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
                      int& outWidth,
                      int& outHeight,
                      int& outComponents,
                      int requiredComponents)
    {
        SGL_FUNCTION();

        unsigned char* data = LoadImageData(filename,
                                            outWidth, outHeight,
                                            outComponents, requiredComponents);
        return STBData(data);
    }
    
} // namespace sgl
