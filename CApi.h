//
// Created by Twiiz on 2023/5/22.
//

#ifndef UNIMAGE_CAPI_H
#define UNIMAGE_CAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifdef UNIMAGE_BUILD
#define UNIMAGE_API __declspec(dllexport)
#elif
#define UNIMAGE_API __declspec(dllimport)
#endif
#elif
#define UNIMAGE_API
#endif

UNIMAGE_API void* unimage_create();
UNIMAGE_API void unimage_free(void* handle);

UNIMAGE_API void unimage_load_raw(void* handle, uint8_t* data, int32_t width, int32_t height, uint8_t format);
UNIMAGE_API uint8_t unimage_load(void* handle, uint8_t* data, uint32_t length);
UNIMAGE_API int32_t unimage_get_width(void* handle);
UNIMAGE_API int32_t unimage_get_height(void* handle);
UNIMAGE_API uint8_t unimage_get_format(void* handle);
UNIMAGE_API uint8_t unimage_copy_to_memory(void* handle, void* buffer);
UNIMAGE_API uint8_t unimage_resize(void* handle, int32_t width, int32_t height);
UNIMAGE_API const char* unimage_get_error_message(void* handle);
UNIMAGE_API uint8_t* unimage_get_buffer(void* handle);
UNIMAGE_API uint8_t unimage_copy_from(void* handle, void* unimage);
UNIMAGE_API uint8_t unimage_clip(void* handle, int32_t x, int32_t y, int32_t width, int32_t height);

#ifdef __cplusplus
};
#endif

#endif //UNIMAGE_CAPI_H
