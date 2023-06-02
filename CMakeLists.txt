cmake_minimum_required(VERSION 3.23)
project(Unimage)

set(CMAKE_CXX_STANDARD 14)

find_package(Stb REQUIRED)
find_package(libjpeg-turbo CONFIG REQUIRED)
find_package(WebP CONFIG REQUIRED)

add_compile_definitions(UNIMAGE_BUILD)

set(LIBRARY_NAME Unimage)
set(LIBRARY_LIBJPEG_NAME libjpeg-turbo::turbojpeg-static)
set(LIBRARY_TYPE SHARED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LIBRARY_NAME libUnimage)
    set(LIBRARY_LIBJPEG_NAME libjpeg-turbo::turbojpeg)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(LIBRARY_TYPE OBJECT)
endif()

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE} loader/StbImpl.cpp loader/StbImpl.hpp Unimage.cpp Unimage.hpp CApi.cpp
        CApi.h loader/WebP.cpp loader/WebP.hpp utils/StaticForLoop.hpp loader/LibJpegTurbo.cpp loader/LibJpegTurbo.hpp ErrorHandler.cpp ErrorHandler.hpp)

target_include_directories(${LIBRARY_NAME} PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(${LIBRARY_NAME} PRIVATE ${LIBRARY_LIBJPEG_NAME})
target_link_libraries(${LIBRARY_NAME} PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)
