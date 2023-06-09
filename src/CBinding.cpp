//
// Created by Twiiz on 2023/5/22.
//

#include "CBinding.h"
#include "UnimageProcessor.hpp"

#define _TypedHandle reinterpret_cast<UnimageProcessor *>(handle)

void* unimage_processor_create()
{
    return new UnimageProcessor;
}

uint8_t unimage_processor_resize(void* handle, int32_t width, int32_t height)
{
    return _TypedHandle->resize(width, height);
}

uint8_t unimage_processor_copy_to_memory(void* handle, void* buffer)
{
    return _TypedHandle->copyToMemory(buffer);
}

uint8_t unimage_processor_get_format(void* handle)
{
    return _TypedHandle->getFormat();
}

int32_t unimage_processor_get_height(void* handle)
{
    return _TypedHandle->getHeight();
}

int32_t unimage_processor_get_width(void* handle)
{
    return _TypedHandle->getWidth();
}

void unimage_processor_free(void* handle)
{
    delete _TypedHandle;
}

void unimage_processor_load_raw(void* handle, uint8_t* data, int32_t width, int32_t height, uint8_t format)
{
    _TypedHandle->loadRawImage(data, width, height, static_cast<UnimageFormat>(format));
}

uint8_t unimage_processor_load(void* handle, uint8_t* data, uint32_t length)
{
    return _TypedHandle->loadImage(data, length);
}

const char* unimage_processor_get_error_message(void* handle)
{
    return _TypedHandle->getErrorMessage().c_str();
}

uint8_t* unimage_processor_get_buffer(void* handle)
{
    return _TypedHandle->getBuffer();
}

uint8_t unimage_processor_copy_from(void* handle, void* unimage)
{
    return _TypedHandle->copyFrom(static_cast<UnimageProcessor*>(unimage));
}

uint8_t unimage_processor_clip(void* handle, int32_t x, int32_t y, int32_t width, int32_t height)
{
    return _TypedHandle->clip(x, y, width, height);
}
