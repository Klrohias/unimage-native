//
// Created by Twiiz on 2023/5/22.
//

#include <cstdlib>
#include <cstring>
#include "UnimageProcessor.hpp"
#include "loader/StbImpl.hpp"
#include "utils/StaticForLoop.hpp"
#include "loader/LibJpegTurbo.hpp"
#include "loader/WebP.hpp"

const char* ERROR_STR_NOT_LOADED = "image is not loaded";
const char* ERROR_STR_OVERFLOW = "range exceeds image size";

template<int PixelSize = 3>
void scaleImage(const uint8_t* srcBuffer, uint8_t* destBuffer, uint32_t srcWidth, uint32_t srcHeight, uint32_t destWidth, uint32_t destHeight)
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

int32_t getPixelSize(UnimageFormat format)
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


UnimageProcessor::UnimageProcessor() = default;

UnimageProcessor::~UnimageProcessor()
{
    releaseImage();
}

void UnimageProcessor::releaseImage()
{
    free(_imageBuffer);
    _imageBuffer = nullptr;

    _width = 0;
    _height = 0;

    _format = None;
}

bool UnimageProcessor::copyFrom(UnimageProcessor* unimage)
{
    if (unimage->_imageBuffer == nullptr)
    {
        _errorHandler.setError(ERROR_STR_NOT_LOADED);
        return false;
    }

    releaseImage();

    loadRawImage(unimage->_imageBuffer, unimage->_width, unimage->_height, unimage->_format);

    return true;
}

bool UnimageProcessor::copyToMemory(void* buffer)
{
    if (!_imageBuffer)
    {
        _errorHandler.setError(ERROR_STR_NOT_LOADED);
        return false;
    }

    uint32_t bufferSize = getPixelSize(_format) * _width * _height;
    memcpy(buffer, _imageBuffer, bufferSize);

    return true;
}

const std::string& UnimageProcessor::getErrorMessage() const
{
    return _errorHandler.getError();
}

int32_t UnimageProcessor::getWidth() const
{
    return _width;
}

int32_t UnimageProcessor::getHeight() const
{
    return _height;
}

UnimageFormat UnimageProcessor::getFormat() const
{
    return _format;
}

uint8_t* UnimageProcessor::getBuffer() const
{
    return _imageBuffer;
}

bool UnimageProcessor::resize(int32_t width, int32_t height)
{
    if (!_imageBuffer)
    {
        _errorHandler.setError(ERROR_STR_NOT_LOADED);
        return false;
    }

    uint32_t bufferSize = getPixelSize(_format) * width * height;
    auto* buffer = static_cast<uint8_t*>(malloc(bufferSize));

    switch (_format)
    {
    case None:break;
    case RGB:
    {
        scaleImage<3>(_imageBuffer, buffer, _width, _height, width, height);
        break;
    }
    case RGBA:
    {
        scaleImage<4>(_imageBuffer, buffer, _width, _height, width, height);
        break;
    }
    }

    free(_imageBuffer);
    _imageBuffer = buffer;
    _width = width;
    _height = height;

    return true;
}

bool UnimageProcessor::clip(int32_t x, int32_t y, int32_t width, int32_t height)
{
    auto pixelSize = getPixelSize(_format);
    auto* newBuffer = static_cast<uint8_t*>(malloc(width * height * pixelSize));

    int32_t srcStrideSize = _width * pixelSize;
    int32_t newStrideSize = width * pixelSize;

    int32_t startLine = _height - y - height;
    int32_t endLine = _height - y;
    int32_t startPixel = x;
    int32_t endPixel = x + width;

    if (startLine < 0 || startLine > _height ||
        endLine < 0 || endLine > _height ||
        startPixel < 0 || startPixel > _width ||
        endPixel < 0 || endPixel > _width)
    {
        _errorHandler.setError(ERROR_STR_OVERFLOW);
        return false;
    }

    for (int iy = 0; iy < height; iy++)
    {
        memcpy(newBuffer + newStrideSize * iy, _imageBuffer + srcStrideSize * (iy + startLine) + x * pixelSize, newStrideSize);
    }

    auto format = _format;
    
    releaseImage();

    _width = width;
    _height = height;
    _format = format;
    _imageBuffer = newBuffer;

    return true;
}

void UnimageProcessor::loadRawImage(uint8_t* data, int32_t width, int32_t height, UnimageFormat format)
{
    releaseImage();

    uint32_t bufferSize = getPixelSize(format) * width * height;
    _imageBuffer = static_cast<uint8_t*>(malloc(bufferSize));

    _format = format;
    _width = width;
    _height = height;

    memcpy(_imageBuffer, data, bufferSize);
}

bool UnimageProcessor::loadImage(uint8_t* data, uint32_t length)
{
    if (IsJpegFormat(data, length))
    {
        return loadImageJpeg(data, length);
    }
    if (IsWebPFormat(data, length))
    {
        return loadImageWebP(data, length);
    }
    return loadImageStb(data, length);
}

bool UnimageProcessor::loadImageStb(uint8_t* data, uint32_t length)
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

bool UnimageProcessor::loadImageJpeg(uint8_t* data, uint32_t length)
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

    loadRawImage(imageData, width, height, getFormatByChannels(channels));

    free(imageData);

    return true;
}

bool UnimageProcessor::loadImageWebP(uint8_t* data, uint32_t length)
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

    loadRawImage(imageData, width, height, getFormatByChannels(channels));

    free(imageData);

    return true;
}
