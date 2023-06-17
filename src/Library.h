//
// Created by Twiiz on 2023/6/17.
//

#ifndef UNIMAGE_LIBRARY_H
#define UNIMAGE_LIBRARY_H

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifdef UNIMAGE_BUILD
#define UNIMAGE_API __declspec(dllexport)
#else
#define UNIMAGE_API __declspec(dllimport)
#endif
#else
#define UNIMAGE_API
#endif

#endif //UNIMAGE_LIBRARY_H
