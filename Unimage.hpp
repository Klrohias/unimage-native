//
// Created by Twiiz on 2023/5/22.
//

#ifndef UNIMAGE_UNIMAGE_HPP
#define UNIMAGE_UNIMAGE_HPP

#include <cstdint>
#include <string>
#include "ErrorHandler.hpp"

enum UnimageFormat : unsigned char
{
    None = 0,
    RGB = 1,
    RGBA = 2,
};

class Unimage
{
    uint8_t* _imageBuffer{nullptr};
    UnimageFormat _format{None};
    uint32_t _width{0};
    uint32_t _height{0};
    ErrorHandler _errorHandler{};

    void releaseImage();

    bool loadImageStb(uint8_t* data, uint32_t length);

    bool loadImageJpeg(uint8_t* data, uint32_t length);

    bool loadImageWebP(uint8_t* data, uint32_t length);

public:
    Unimage();

    ~Unimage();

    void LoadRawImage(uint8_t* data, uint32_t width, uint32_t height, UnimageFormat format);

    bool LoadImage(uint8_t* data, uint32_t length);

    uint32_t GetWidth() const;

    uint32_t GetHeight() const;

    UnimageFormat GetFormat() const;

    bool CopyTo(void* buffer);

    bool Resize(uint32_t width, uint32_t height);

    const std::string& GetErrorMessage() const;

};


#endif //UNIMAGE_UNIMAGE_HPP
