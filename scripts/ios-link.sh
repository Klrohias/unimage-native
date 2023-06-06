#!/bin/zsh
echo "vcpkg root path: $1"

VCPKG_ROOT=$1

OUTPUT_DIR=$(pwd)

mkdir _ARCHIVE
pushd _ARCHIVE

TRIPLET=arm64-ios-bitcode
PACKAGES=$VCPKG_ROOT/packages

function ExtractVcpkgArchive {
    ar x $PACKAGES/$1_$TRIPLET/lib/$2
}

function ExtractArchive {
    ar x $1
}

function MergeArchive {
    rm $OUTPUT_DIR/$1
    ar cru $OUTPUT_DIR/$1 *.o
}


ExtractArchive $OUTPUT_DIR/libUnimage.a
ExtractVcpkgArchive libjpeg-turbo libturbojpeg.a
ExtractVcpkgArchive libwebp libwebp.a
ExtractVcpkgArchive libwebp libwebpdecoder.a
ExtractVcpkgArchive libwebp libwebpdemux.a
MergeArchive libUnimage.a

popd
rm -rf _ARCHIVE
