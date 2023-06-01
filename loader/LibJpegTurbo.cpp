//
// Created by Twiiz on 2023/5/26.
//

#include "LibJpegTurbo.hpp"
#include <turbojpeg.h>
#include <cstring>

const uint8_t jpegMagicNumber[] = {0xff, 0xd8, 0xff, 0xe0};

bool IsJpegFormat(uint8_t* data, uint32_t size)
{
    if (size < 4)return false;
    return memcmp(data, jpegMagicNumber, 4) == 0;
}


uint8_t* tj3DecodeFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler* errorHandler)
{
    tjhandle processor = nullptr;
    uint8_t* transformedData = nullptr;
    uint64_t transformedSize = 0;
    uint8_t* buffer = nullptr;
    try
    {
        // transform
        processor = tjInitTransform();
        tjtransform transform{};
        memset(&transform, 0, sizeof(tjtransform));
        transform.op = TJXOP_VFLIP;

        if (tjTransform(processor, data, size, 1, &transformedData,
                        reinterpret_cast<unsigned long*>(&transformedSize), &transform, 0) != 0)
        {
            errorHandler->setErrorAndThrow(tjGetErrorStr2(processor));
        }

        tjDestroy(processor);

        // decode
        processor = tjInitDecompress();

        int jpegSubsample, jpegColorspace;
        if (tjDecompressHeader3(processor, data,
                                size, width, height, &jpegSubsample, &jpegColorspace) != 0)
        {
            errorHandler->setErrorAndThrow(tjGetErrorStr2(processor));
        }

        (*channels) = 3;

        // decode
        buffer = static_cast<uint8_t*>(malloc((*width) * (*height) * 3)); // RGB
        if (tjDecompress2(processor, transformedData, transformedSize, buffer, *width, 0, *height, TJPF_RGB, TJFLAG_FASTDCT) != 0)
        {
            errorHandler->setErrorAndThrow(tjGetErrorStr2(processor));
        }

        tjFree(transformedData);
        tjDestroy(processor);

        return buffer;
    } catch (const std::exception& ex)
    {
        if (processor) tjDestroy(processor);
        if (transformedData) tjFree(transformedData);
        if (buffer) free(buffer);
        throw;
    }
}
