//
// Created by Twiiz on 2023/5/22.
//

#include "CBinding.h"
#include "UnimageProcessor.hpp"

#define TypedHandle_ (reinterpret_cast<UnimageProcessor *>(handle))

CBINDING_METHOD(CBINDING_TYPED_PTR(UnimageProcess), UnimageProcessor, Create) {
    return new UnimageProcessor;
}

CBINDING_METHOD(void, UnimageProcessor, Free, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    delete TypedHandle_;
}

CBINDING_METHOD(void, UnimageProcessor, LoadRaw, CBINDING_TYPED_PTR(UnimageProcessor) handle, uint8_t* data,
                int32_t width, int32_t height, CBINDING_ENUM_U8(UnimageFormat) format) {
    TypedHandle_->loadRawImage(data, width, height, static_cast<UnimageFormat>(format));
}

CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Load, CBINDING_TYPED_PTR(UnimageProcessor) handle, uint8_t* data,
                uint32_t length) {
    return TypedHandle_->loadImage(data, length);
}

CBINDING_METHOD(uint32_t, UnimageProcessor, GetWidth, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    return TypedHandle_->getWidth();
}

CBINDING_METHOD(uint32_t, UnimageProcessor, GetHeight, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    return TypedHandle_->getHeight();
}

CBINDING_METHOD(uint8_t, UnimageProcessor, GetFormat, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    return TypedHandle_->getFormat();
}

CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, CopyToMemory, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                void* buffer) {
    return TypedHandle_->copyToMemory(buffer);
}

CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Resize, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                int32_t width, int32_t height) {
    return TypedHandle_->resize(width, height);
}

CBINDING_METHOD(CBINDING_CSTRING, UnimageProcessor, GetErrorMessage, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    return TypedHandle_->getErrorMessage().c_str();
}

CBINDING_METHOD(uint8_t*, UnimageProcessor, GetBuffer, CBINDING_TYPED_PTR(UnimageProcessor) handle) {
    return TypedHandle_->getBuffer();
}

CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, CopyFrom, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                CBINDING_TYPED_PTR(UnimageProcessor) other) {
    return TypedHandle_->copyFrom(static_cast<UnimageProcessor*>(other));
}

CBINDING_METHOD(CBINDING_BOOLEAN, UnimageProcessor, Clip, CBINDING_TYPED_PTR(UnimageProcessor) handle,
                int32_t x, int32_t y, int32_t width, int32_t height) {
    return TypedHandle_->clip(x, y, width, height);
}

#undef TypedHandle_