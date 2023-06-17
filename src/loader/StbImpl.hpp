//
// Created by Twiiz on 2023/5/22.
//

#ifndef UNIMAGE_STBIMPL_HPP
#define UNIMAGE_STBIMPL_HPP

#include <stb_image.h>
#include <cstdint>
#include "utils/ErrorHandler.hpp"

uint8_t* stbDecodeFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler *errorHandler);

#endif //UNIMAGE_STBIMPL_HPP
