#!/bin/zsh
echo "[iOS-build] vcpkg root path: $1"

VCPKG_DIR=$1
OUTPUT_DIR=$(pwd)
SCRIPT_DIR=$(dirname $0)
PACKAGES_DIR=$VCPKG_DIR/packages

TRIPLET=arm64-ios-bitcode

function ExtractVcpkgArchive {
    ar x $PACKAGES_DIR/$1_$TRIPLET/lib/$2
}

function ExtractArchive {
    echo "[iOS-build] extract library: $1"
    ar x $1
}

mkdir _ARCHIVE
pushd _ARCHIVE

# Extract all archives
ExtractArchive $OUTPUT_DIR/libUnimage.a
ExtractVcpkgArchive libjpeg-turbo libturbojpeg.a
ExtractVcpkgArchive libwebp libwebp.a
ExtractVcpkgArchive libwebp libwebpdecoder.a
ExtractVcpkgArchive libwebp libwebpdemux.a

# Link all objects
echo "[iOS-build] link objects"
ld -r *.o -o $OUTPUT_DIR/libUnimage.o -bitcode_bundle -exported_symbols_list $SCRIPT_DIR/export-symbols.txt
rm $OUTPUT_DIR/libUnimage.a
ar -q $OUTPUT_DIR/libUnimage.a $OUTPUT_DIR/libUnimage.o
ranlib $OUTPUT_DIR/libUnimage.a

popd
rm -rf _ARCHIVE

