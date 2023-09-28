cmake_minimum_required(VERSION 3.23)

# Package
set(UNIMAGE_VERSION 0.1.5)
project(Unimage
    VERSION ${UNIMAGE_VERSION}
    DESCRIPTION "A wrapper of libjpeg-turbo, libwebp, stb."
    HOMEPAGE_URL "https://github.com/Klrohias/unimage-native"
    LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)

# Dependencies
find_package(Stb REQUIRED)
find_package(libjpeg-turbo CONFIG REQUIRED)
find_package(WebP CONFIG REQUIRED)

# Config
if (BUILD_SHARED_LIBS AND WIN32)
	add_compile_definitions(UNIMAGE_BUILD)
endif()

set(LINK_LIBJPEG_NAME libjpeg-turbo::turbojpeg-static)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(LINK_LIBJPEG_NAME libjpeg-turbo::turbojpeg)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
	set(BUILD_SHARED_LIBS no)
endif()

# Compile
add_library(Unimage src/loader/StbImpl.cpp src/loader/StbImpl.hpp src/UnimageProcessor.cpp src/UnimageProcessor.hpp src/CBinding.cpp
		src/CBinding.h src/loader/WebP.cpp src/loader/WebP.hpp src/utils/StaticForLoop.hpp src/loader/LibJpegTurbo.cpp src/loader/LibJpegTurbo.hpp
		src/utils/ErrorHandler.cpp src/utils/ErrorHandler.hpp src/Library.h)

add_library(klrohias::unimage ALIAS Unimage)

# Link
if (UNIMAGE_UNITY AND (${CMAKE_SYSTEM_NAME} MATCHES "iOS"))
	message("Enable static linking for iOS...")
    add_custom_command(
        TARGET Unimage
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/scripts/unity-ios-link.sh ${VCPKG_INSTALLED_DIR}/../
    )
endif()

target_compile_features(Unimage PUBLIC cxx_std_14)
target_include_directories(Unimage
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Dependencies
target_include_directories(Unimage PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(Unimage PRIVATE ${LINK_LIBJPEG_NAME})
target_link_libraries(Unimage PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)

# Package Config
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

install(TARGETS Unimage EXPORT unimage-targets)

install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/unimage
        FILES_MATCHING
        PATTERN "*.h*")

install(EXPORT unimage-targets
	NAMESPACE klrohias::
	DESTINATION ${UNIMAGE_INSTALL_DST})
