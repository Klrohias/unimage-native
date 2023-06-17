//
// Created by Twiiz on 2023/5/22.
//

#ifndef UNIMAGE_CBINDING_H
#define UNIMAGE_CBINDING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "Library.h"

UNIMAGE_API void* unimage_processor_create();
UNIMAGE_API void unimage_processor_free(void* handle);

UNIMAGE_API void unimage_processor_load_raw(void* handle, uint8_t* data, int32_t width, int32_t height, uint8_t format);
UNIMAGE_API uint8_t unimage_processor_load(void* handle, uint8_t* data, uint32_t length);
UNIMAGE_API int32_t unimage_processor_get_width(void* handle);
UNIMAGE_API int32_t unimage_processor_get_height(void* handle);
UNIMAGE_API uint8_t unimage_processor_get_format(void* handle);
UNIMAGE_API uint8_t unimage_processor_copy_to_memory(void* handle, void* buffer);
UNIMAGE_API uint8_t unimage_processor_resize(void* handle, int32_t width, int32_t height);
UNIMAGE_API const char* unimage_processor_get_error_message(void* handle);
UNIMAGE_API uint8_t* unimage_processor_get_buffer(void* handle);
UNIMAGE_API uint8_t unimage_processor_copy_from(void* handle, void* unimage);
UNIMAGE_API uint8_t unimage_processor_clip(void* handle, int32_t x, int32_t y, int32_t width, int32_t height);

#ifdef __cplusplus
};
#endif

#endif //UNIMAGE_CBINDING_H
