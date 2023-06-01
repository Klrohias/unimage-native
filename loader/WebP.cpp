//
// Created by Twiiz on 2023/5/26.
//

#include "WebP.hpp"

#include <webp/decode.h>

bool IsWebPFormat(const uint8_t* data, uint32_t length)
{
    if (length < 15)
        return false;

    return data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F';
}

uint8_t* loadWebpFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler* errorHandler)
{
    if(!WebPGetInfo(data, size, width, height)){
        errorHandler->setErrorAndThrow("Failed to get webp info");
    }

    // TODO

    (*channels) = 4;

    auto* result = WebPDecodeRGBA(data, size, width, height);
    if (!result)
    {
        errorHandler->setErrorAndThrow("failed to decode webp");
    }

    return result;
}


void freeWebpData(uint8_t* data)
{
    WebPFree(data);
}
