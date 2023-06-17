cmake_minimum_required(VERSION 3.23)

set(UNIMAGE_VERSION 0.1.3)
project(Unimage
    VERSION ${UNIMAGE_VERSION}
    DESCRIPTION "A wrapper of libjpeg-turbo, libwebp, stb."
    HOMEPAGE_URL "https://github.com/Klrohias/unimage-native"
    LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)

find_package(Stb REQUIRED)
find_package(libjpeg-turbo CONFIG REQUIRED)
find_package(WebP CONFIG REQUIRED)

add_compile_definitions(UNIMAGE_BUILD)

set(LIBRARY_NAME Unimage)
set(LIBRARY_LIBJPEG_NAME libjpeg-turbo::turbojpeg-static)
set(LIBRARY_TYPE SHARED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
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

add_library(klrohias::unimage ALIAS ${LIBRARY_NAME})

if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    # link
    message("Building for iOS")
    
    add_custom_command(
        TARGET ${LIBRARY_NAME}
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/scripts/ios-link.sh ${VCPKG_INSTALLED_DIR}/../
    )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(${LIBRARY_NAME} PROPERTIES PREFIX "lib")
    # TODO: Remove prefix in next version
endif()

target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
target_include_directories(${LIBRARY_NAME}
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(${LIBRARY_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} PRIVATE ${LIBRARY_LIBJPEG_NAME})
target_link_libraries(${LIBRARY_NAME} PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)

set(UNIMAGE_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR}/unimage-config.cmake)
set(UNIMAGE_INSTALL_DST ${CMAKE_INSTALL_DATADIR}/unimage)
configure_package_config_file(scripts/unimage-config.cmake.in
	${UNIMAGE_CONFIG_PATH}
	INSTALL_DESTINATION ${UNIMAGE_INSTALL_DST}
	NO_SET_AND_CHECK_MACRO)

set(UNIMAGE_CONFIG_VERSION_PATH ${CMAKE_CURRENT_BINARY_DIR}/unimage-config-version.cmake)
write_basic_package_version_file(
	${UNIMAGE_CONFIG_VERSION_PATH}
	VERSION ${UNIMAGE_VERSION}
	COMPATIBILITY SameMajorVersion)

install(
	FILES
		${UNIMAGE_CONFIG_PATH}
		${UNIMAGE_CONFIG_VERSION_PATH}
	DESTINATION
		${UNIMAGE_INSTALL_DST})

install(TARGETS ${LIBRARY_NAME} EXPORT unimage-targets)

install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h*")

install(EXPORT unimage-targets
	NAMESPACE klrohias::
	DESTINATION ${UNIMAGE_INSTALL_DST})
