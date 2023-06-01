//
// Created by Twiiz on 2023/5/22.
//

#include "CApi.h"
#include "Unimage.hpp"

#define _TypedHandle reinterpret_cast<Unimage *>(handle)

void* unimage_create()
{
    return new Unimage;
}

uint8_t unimage_resize(void* handle, uint32_t width, uint32_t height)
{
    return _TypedHandle->Resize(width, height);
}

uint8_t unimage_copy_to(void* handle, void* buffer)
{
    return _TypedHandle->CopyTo(buffer);
}

uint8_t unimage_get_format(void* handle)
{
    return _TypedHandle->GetFormat();
}

uint32_t unimage_get_height(void* handle)
{
    return _TypedHandle->GetHeight();
}

uint32_t unimage_get_width(void* handle)
{
    return _TypedHandle->GetWidth();
}

void unimage_free(void* handle)
{
    delete _TypedHandle;
}

void unimage_load_raw(void* handle, uint8_t* data, uint32_t width, uint32_t height, uint8_t format)
{
    _TypedHandle->LoadRawImage(data, width, height, static_cast<UnimageFormat>(format));
}

uint8_t unimage_load(void* handle, uint8_t* data, uint32_t length)
{
    return _TypedHandle->LoadImage(data, length);
}

const char* unimage_get_error_message(void* handle)
{
    return _TypedHandle->GetErrorMessage().c_str();
}