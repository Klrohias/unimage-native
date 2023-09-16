#!/bin/zsh

VCPKG_DIR=$1
OUTPUT_DIR=$(pwd)
SCRIPT_DIR=$(dirname $0)
PACKAGES_DIR=$VCPKG_DIR/packages

TRIPLET=arm64-ios-bitcode

echo "[iOS-build] ===== Unimage iOS Post-build Script ====="
echo "[iOS-build] VCPKG_DIR: $VCPKG_DIR"
echo "[iOS-build] OUTPUT_DIR: $OUTPUT_DIR"
echo "[iOS-build] SCRIPT_DIR: $SCRIPT_DIR"
echo "[iOS-build] PACKAGES_DIR: $PACKAGES_DIR"
echo "[iOS-build] TRIPLET: $TRIPLET"

echo "[iOS-build] List Of $OUTPUT_DIR"
ls -al $OUTPUT_DIR

function ExtractVcpkgArchive {
    ar x $PACKAGES_DIR/$1_$TRIPLET/lib/$2
}

function ExtractArchive {
    echo "[iOS-build] Extract library: $1"
    ar x $1
}

mkdir _ARCHIVE
pushd _ARCHIVE

echo "[iOS-build] Extract libraries"

# Extract all archives
ExtractArchive $OUTPUT_DIR/libUnimage.a
ExtractVcpkgArchive libjpeg-turbo libturbojpeg.a
ExtractVcpkgArchive libwebp libwebp.a
ExtractVcpkgArchive libwebp libwebpdecoder.a
ExtractVcpkgArchive libwebp libwebpdemux.a

# Link all objects
echo "[iOS-build] Link objects"
ld -r *.o -o $OUTPUT_DIR/libUnimage.o -bitcode_bundle -exported_symbols_list $SCRIPT_DIR/export-symbols.txt
rm $OUTPUT_DIR/libUnimage.a
ar -q $OUTPUT_DIR/libUnimage.a $OUTPUT_DIR/libUnimage.o
ranlib $OUTPUT_DIR/libUnimage.a

popd
rm -rf _ARCHIVE

