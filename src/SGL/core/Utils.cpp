/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/core/Utils.h"

#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


namespace sgl
{
    std::vector<char> LoadFile(std::string_view filename)
    {
        SGL_LOG_INFO("Loading file: {}", filename);

        // Open reading from the end, read as binary
        std::ifstream file( filename.data(),
                            std::ios::ate | std::ios::binary );
        SGL_ASSERT_MSG(file.is_open(), "Failed to open a file '{}'", filename);

        if (!file.is_open())
        {
            std::cerr << "Failed to open a file: '" << filename << "'\n";
            exit(1);
        }

        // Use read position to determine the size of the file
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        // Seek back to the beginning of the file and read all of the bytes
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    std::string LoadTextFile(std::string_view filename)
    {
        SGL_LOG_INFO("Loading Text file: {}", filename);

        std::ifstream inFile( filename.data() );
        SGL_ASSERT_MSG(inFile.is_open(),
                        "Failed to open a file '{}'", filename);
        if (!inFile.is_open())
        {
            std::cerr << "Failed to open a file: '" << filename << "'\n";
            exit(1);
        }

        return { std::istreambuf_iterator<char>(inFile), 
                 std::istreambuf_iterator<char>() };
    }

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

    STBData::STBData()
        : STBData(0, 0, 0, NULL)
    {

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
