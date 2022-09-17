/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_UTILS_H_
#define SGL_CORE_UTILS_H_


namespace sgl
{
    /**
     * @brief Reads contents of a file as binary
     * @param filename The file to read from
     * @return Vector of characters from read binary data
     */
    std::vector<char> LoadFile(std::string_view filename);

    /**
     * @brief Reads file as a text
     * @param filename The file to read from
     */
    std::string LoadTextFile(std::string_view filename);

    /**
     * @brief Loads image into memory, MUST FREE memory manually using
     * 'FreeImageMemory()'.
     * For more info @see stb_image.h at http://nothings.org/stb 
     * @param outWidth Outputs image width in pixels
     * @param outHeight Outputs image height in pixels
     * @param outComponents Outputs # of image components in the image
     * @param requiredComponents Force # of image components in the result
     * @return Pixel data or NULL on an allocation failure, or an invalid image
     */
    unsigned char* LoadImageData(const char* filename,
                                 int& outWidth,
                                 int& outHeight,
                                 int& outComponents,
                                 int requiredComponents = 0);

    /** @param data Pixel data allocated by 'LoadImage()' */
    void FreeImageData(unsigned char* data);

    /** @brief Abstraction for data loaded using STBI library, 
     *  frees memory out of scope.
     */
    struct STBData
    {
        int width;
        int height;
        int channels;
        unsigned char* data;

        STBData();
        STBData(int w, int h, int ch, unsigned char* p);
        ~STBData();

        operator bool() const { return data != NULL; }
        operator unsigned char*() const { return data; }

        bool Loaded() const { return bool(data); }
    };

    /**
     * @brief Loads image into memory, STBData instance is automatically freed
     *  when out of scope. For more info @see stb_image.h at http://nothings.org/stb 
     * @param requiredComponents Force # of image components in the result
     * @return Pixel data or NULL on an allocation failure, or an invalid image
     */
    STBData LoadImage(const char* filename,
                      int requiredComponents = 0);
    
} // namespace sgl


#endif // SGL_CORE_UTILS_H_
