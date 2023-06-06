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
    set(LIBRARY_TYPE STATIC)
    
    # enable bitcode
    set(CMAKE_CXX_FLAGS -fembed-bitcode)
    set(CMAKE_C_FLAGS -fembed-bitcode)
endif()

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE} src/loader/StbImpl.cpp src/loader/StbImpl.hpp src/Unimage.cpp src/Unimage.hpp src/CApi.cpp
        src/CApi.h src/loader/WebP.cpp src/loader/WebP.hpp src/utils/StaticForLoop.hpp src/loader/LibJpegTurbo.cpp src/loader/LibJpegTurbo.hpp 
	src/ErrorHandler.cpp src/ErrorHandler.hpp)


if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    # link
    message("Building for iOS")
    
    add_custom_command(
        TARGET ${LIBRARY_NAME}
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/scripts/ios-link.sh ${VCPKG_INSTALLED_DIR}/../
    )
endif()

target_include_directories(${LIBRARY_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} PRIVATE ${LIBRARY_LIBJPEG_NAME})
target_link_libraries(${LIBRARY_NAME} PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)
