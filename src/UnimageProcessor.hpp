//
// Created by Twiiz on 2023/5/22.
//

#ifndef UNIMAGE_UNIMAGEPROCESSOR_HPP
#define UNIMAGE_UNIMAGEPROCESSOR_HPP

#include <cstdint>
#include <string>
#include "utils/ErrorHandler.hpp"
#include "Library.h"

enum UnimageFormat : unsigned char
{
    None = 0,
    RGB = 1,
    RGBA = 2,
};

class UnimageProcessor
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
    UNIMAGE_API UnimageProcessor();

    UNIMAGE_API ~UnimageProcessor();

    UNIMAGE_API void loadRawImage(uint8_t* data, int32_t width, int32_t height, UnimageFormat format);

    UNIMAGE_API bool loadImage(uint8_t* data, uint32_t length);

    UNIMAGE_API int32_t getWidth() const;

    UNIMAGE_API int32_t getHeight() const;

    UNIMAGE_API UnimageFormat getFormat() const;

    UNIMAGE_API uint8_t* getBuffer() const;

    UNIMAGE_API const std::string& getErrorMessage() const;

    UNIMAGE_API bool copyToMemory(void* buffer);

    UNIMAGE_API bool copyFrom(UnimageProcessor* unimage);

    UNIMAGE_API bool resize(int32_t width, int32_t height);

    UNIMAGE_API bool clip(int32_t x, int32_t y, int32_t width, int32_t height);
};


#endif //UNIMAGE_UNIMAGEPROCESSOR_HPP
