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

#define CBINDING_TYPED_PTR(TYPE) void*
#define CBINDING_METHOD(RETURN_VALUE, CLASS_NAME, METHOD_NAME, ...) UNIMAGE_API RETURN_VALUE UNIMAGE_##CLASS_NAME##_##METHOD_NAME \
    (__VA_ARGS__)
#define CBINDING_BOOLEAN uint8_t
#define CBINDING_CSTRING const char*
#define CBINDING_ENUM_U8(TYPE) uint8_t

CBINDING_METHOD(CBINDING_TYPED_PTR(UnimageProcess), UnimageProcessor, Create);
CBINDING_METHOD(void, UnimageProcessor, Free, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(void, UnimageProcessor, LoadRaw, CBINDING_TYPED_PTR(UnimageProcessor) handle, uint8_t* data,
                int32_t width, int32_t height, CBINDING_ENUM_U8(UnimageFormat) format);
CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Load, CBINDING_TYPED_PTR(UnimageProcessor) handle, uint8_t* data,
                uint32_t length);
CBINDING_METHOD(uint32_t, UnimageProcessor, GetWidth, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(uint32_t, UnimageProcessor, GetHeight, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(uint8_t, UnimageProcessor, GetFormat, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, CopyToMemory, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                void* buffer);
CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Resize, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                int32_t width, int32_t height);
CBINDING_METHOD(CBINDING_CSTRING, UnimageProcessor, GetErrorMessage, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(uint8_t*, UnimageProcessor, GetBuffer, CBINDING_TYPED_PTR(UnimageProcessor) handle);
CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, CopyFrom, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                CBINDING_TYPED_PTR(UnimageProcessor) other);
CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Clip, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                int32_t x, int32_t y, int32_t width, int32_t height);

#ifdef __cplusplus
};
#endif

#endif //UNIMAGE_CBINDING_H
