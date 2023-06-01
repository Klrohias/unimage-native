#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include "StbImpl.hpp"


uint8_t* stbDecodeFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler* errorHandler)
{
    stbi_set_flip_vertically_on_load(true);

    uint8_t* buffer = stbi_load_from_memory(data, size, width, height, channels, 0);
    if (!buffer)
    {
        errorHandler->setErrorAndThrow(stbi_failure_reason());
    }

    return buffer;
}

