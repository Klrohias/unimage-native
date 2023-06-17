//
// Created by Twiiz on 2023/5/26.
//

#ifndef UNIMAGE_LIBJPEGTURBO_HPP
#define UNIMAGE_LIBJPEGTURBO_HPP

#include <cstdint>
#include <string>
#include "utils/ErrorHandler.hpp"

bool IsJpegFormat(uint8_t* data, uint32_t size);

uint8_t* tj3DecodeFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler *errorHandler);

#endif //UNIMAGE_LIBJPEGTURBO_HPP
