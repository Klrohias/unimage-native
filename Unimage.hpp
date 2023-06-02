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
    int32_t _width{0};
    int32_t _height{0};
    ErrorHandler _errorHandler{};

    void releaseImage();

    bool loadImageStb(uint8_t* data, uint32_t length);

    bool loadImageJpeg(uint8_t* data, uint32_t length);

    bool loadImageWebP(uint8_t* data, uint32_t length);

public:
    Unimage();

    ~Unimage();

    void loadRawImage(uint8_t* data, int32_t width, int32_t height, UnimageFormat format);

    bool loadImage(uint8_t* data, uint32_t length);

    int32_t getWidth() const;

    int32_t getHeight() const;

    UnimageFormat getFormat() const;

    uint8_t* getBuffer() const;

    const std::string& getErrorMessage() const;

    bool copyToMemory(void* buffer);

    bool copyFrom(Unimage* unimage);

    bool resize(int32_t width, int32_t height);

    bool clip(int32_t x, int32_t y, int32_t width, int32_t height);
};


#endif //UNIMAGE_UNIMAGE_HPP
