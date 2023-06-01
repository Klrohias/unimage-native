cmake_minimum_required(VERSION 3.23)
project(Unimage)

set(CMAKE_CXX_STANDARD 14)

find_package(Stb REQUIRED)
find_package(libjpeg-turbo CONFIG REQUIRED)
find_package(WebP CONFIG REQUIRED)

add_compile_definitions(UNIMAGE_BUILD)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(LIBRARY_TYPE SHARED)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LIBRARY_TYPE SHARED)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LIBRARY_TYPE SHARED)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(LIBRARY_TYPE SHARED)
endif()
if (${UNIMAGE_IOS})
    set(LIBRARY_TYPE OBJECT)
endif()

add_library(libUnimage ${LIBRARY_TYPE} loader/StbImpl.cpp loader/StbImpl.hpp Unimage.cpp Unimage.hpp CApi.cpp
        CApi.h loader/WebP.cpp loader/WebP.hpp utils/StaticForLoop.hpp loader/LibJpegTurbo.cpp loader/LibJpegTurbo.hpp ErrorHandler.cpp ErrorHandler.hpp)

target_include_directories(libUnimage PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(libUnimage PRIVATE libjpeg-turbo::turbojpeg)
target_link_libraries(libUnimage PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)
