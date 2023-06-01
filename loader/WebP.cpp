//
// Created by Twiiz on 2023/5/26.
//

#include "WebP.hpp"

#include <webp/decode.h>
#include <memory>

bool IsWebPFormat(const uint8_t* data, uint32_t length)
{
    if (length < 15)
        return false;

    return data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F';
}

uint8_t* loadWebpFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler* errorHandler)
{
    if (!WebPGetInfo(data, size, width, height))
    {
        errorHandler->setErrorAndThrow("Failed to get webp info");
    }

    uint8_t* buffer = nullptr;
    (*channels) = 4;

    try
    {
        buffer = static_cast<uint8_t*>(malloc((*width) * (*height) * (*channels)));

        VP8StatusCode statusCode = VP8_STATUS_OK;

        WebPDecoderConfig decoderConfig;

        if (WebPInitDecoderConfig(&decoderConfig) == 0)
        {
            errorHandler->setErrorAndThrow("Failed to initialize decoder config");
        }


        decoderConfig.options.use_threads = true;
        decoderConfig.options.use_scaling = false;
        if ((statusCode = WebPGetFeatures(data, size, &decoderConfig.input)) != VP8_STATUS_OK)
        {
            errorHandler->setErrorAndThrow("Failed to call WebPGetFeatures: " + std::to_string(statusCode));
        }

        auto strideSize = (*channels) * (*width);

        decoderConfig.output.is_external_memory = true;
        decoderConfig.output.colorspace = MODE_RGBA;
        decoderConfig.output.u.RGBA.stride = -strideSize;
        decoderConfig.output.u.RGBA.rgba = buffer + ((*height) - 1) * strideSize;
        decoderConfig.output.u.RGBA.size = (*height) * strideSize;
        decoderConfig.output.width = *width;
        decoderConfig.output.height = *height;

        if ((statusCode = WebPDecode(data, size, &decoderConfig)) != VP8_STATUS_OK)
        {
            errorHandler->setErrorAndThrow("Failed to call WebPDecode: " + std::to_string(statusCode));
        }

        return buffer;
    } catch (const std::exception& ex)
    {
        free(buffer);
        throw;
    }
}
