//
// Created by Twiiz on 2023/5/26.
//

#ifndef UNIMAGE_WEBP_HPP
#define UNIMAGE_WEBP_HPP

#include <cstdint>
#include <string>
#include "../ErrorHandler.hpp"

bool IsWebPFormat(const uint8_t* data, uint32_t length);

uint8_t* loadWebpFromMemory(uint8_t* data, uint32_t size, int* width, int* height, int* channels, ErrorHandler* errorHandler);

#endif //UNIMAGE_WEBP_HPP
