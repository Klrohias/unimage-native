//
// Created by Twiiz on 2023/5/22.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Unimage.hpp"
#include "./loader/StbImpl.hpp"
#include "utils/StaticForLoop.hpp"
#include "loader/LibJpegTurbo.hpp"
#include "loader/WebP.hpp"

template<int PixelSize = 3>
void Scale(const uint8_t* srcBuffer, uint8_t* destBuffer, uint32_t srcWidth, uint32_t srcHeight, uint32_t destWidth, uint32_t destHeight)
{
    float scaleX, scaleY;
    scaleX = (float) srcWidth / (float) destWidth;
    scaleY = (float) srcHeight / (float) destHeight;

    for (int ix = 0; ix < destWidth; ix++)
    {
        for (int iy = 0; iy < destHeight; iy++)
        {
            int px, py;
            px = (int) (ix * scaleX);
            py = (int) (iy * scaleY);
            uint32_t destPixelBegin = destWidth * iy + ix;
            uint32_t srcPixelBegin = srcWidth * py + px;
            static_for<0, PixelSize>()([&](int i)
                                       {
                                           destBuffer[destPixelBegin * PixelSize + i] = srcBuffer[srcPixelBegin * PixelSize + i];
                                       });
        }
    }
}

uint32_t getPixelSize(UnimageFormat format)
{
    switch (format)
    {
    case RGB: return 3;
    case RGBA: return 4;
    default: return 0;
    }
}

UnimageFormat getFormatByChannels(int channels)
{
    switch (channels)
    {
    case 3: return RGB;
    case 4: return RGBA;
    default: return None;
    }
}

Unimage::Unimage() = default;

Unimage::~Unimage()
{
    releaseImage();
}

void Unimage::releaseImage()
{
    free(_imageBuffer);
    _imageBuffer = nullptr;

    _width = 0;
    _height = 0;

    _format = None;
}

void Unimage::LoadRawImage(uint8_t* data, uint32_t width, uint32_t height, UnimageFormat format)
{
    releaseImage();

    uint32_t bufferSize = getPixelSize(format) * width * height;
    _imageBuffer = static_cast<uint8_t*>(malloc(bufferSize));

    _format = format;
    _width = width;
    _height = height;

    memcpy(_imageBuffer, data, bufferSize);
}

bool Unimage::LoadImage(uint8_t* data, uint32_t len)
{
    if (IsJpegFormat(data, len))
    {
        return loadImageJpeg(data, len);
    }
    if (IsWebPFormat(data, len))
    {
        return loadImageWebP(data, len);
    }
    return loadImageStb(data, len);
}

uint32_t Unimage::GetWidth() const
{
    return _width;
}

uint32_t Unimage::GetHeight() const
{
    return _height;
}

UnimageFormat Unimage::GetFormat() const
{
    return _format;
}

bool Unimage::CopyTo(void* buffer)
{
    if (!_imageBuffer)
    {
        _errorHandler.setError("image is not loaded");
        return false;
    }

    uint32_t bufferSize = getPixelSize(_format) * _width * _height;
    memcpy(buffer, _imageBuffer, bufferSize);

    return true;
}

bool Unimage::Resize(uint32_t width, uint32_t height)
{
    if (!_imageBuffer)
    {
        _errorHandler.setError("image is not loaded");
        return false;
    }

    uint32_t bufferSize = getPixelSize(_format) * width * height;
    auto* buffer = static_cast<uint8_t*>(malloc(bufferSize));

    switch (_format)
    {
    case None:break;
    case RGB:
    {
        Scale<3>(_imageBuffer, buffer, _width, _height, width, height);
        break;
    }
    case RGBA:
    {
        Scale<4>(_imageBuffer, buffer, _width, _height, width, height);
        break;
    }
    }

    free(_imageBuffer);
    _imageBuffer = buffer;
    _width = width;
    _height = height;

    return true;
}

const std::string& Unimage::GetErrorMessage() const
{
    return _errorHandler.getError();
}

bool Unimage::loadImageStb(uint8_t* data, uint32_t length)
{

    int width = 0, height = 0, channels = 0;
    uint8_t* imageData = nullptr;

    if (!_errorHandler.run([&]()
                           {
                               imageData = stbDecodeFromMemory(data, length, &width, &height, &channels, &_errorHandler);
                           }))
    {
        return false;
    }

    releaseImage();

    _width = width;
    _height = height;
    _format = getFormatByChannels(channels);

    uint32_t bufferSize = width * height * channels;

    _imageBuffer = static_cast<uint8_t*>(malloc(bufferSize));

    memcpy(_imageBuffer, imageData, bufferSize);

    stbi_image_free(imageData);

    return true;
}

bool Unimage::loadImageJpeg(uint8_t* data, uint32_t length)
{
    int width, height, channels;
    uint8_t* imageData = nullptr;


    if (!_errorHandler.run([&]()
                           {
                               imageData = tj3DecodeFromMemory(data, length, &width, &height, &channels, &_errorHandler);
                           }))
    {
        return false;
    }

    LoadRawImage(imageData, width, height, getFormatByChannels(channels));

    free(imageData);

    return true;
}

bool Unimage::loadImageWebP(uint8_t* data, uint32_t length)
{
    int width, height, channels;
    uint8_t* imageData = nullptr;
    if (!_errorHandler.run([&]()
                           {
                               imageData = loadWebpFromMemory(data, length, &width, &height, &channels, &_errorHandler);
                           }))
    {
        return false;
    }

    LoadRawImage(imageData, width, height, getFormatByChannels(channels));

    free(imageData);

    return true;
}
