# Unimage Native
Used by [unimage-unity](https://github.com/Klrohias/unimage-unity).  
It can load `png`/`jpeg`/`webp`/`bmp`/`tga`/`gif` in to memory, and provides some simple operations.

# Building
### 1. Install dependencies
```shell
./vcpkg install stb
./vcpkg install libwebp
./vcpkg install libjpeg-turbo
```

### 2. Generate for special platform:  
#### 1) Windows:
```shell
# PowerShell
cd path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
msbuild ALL_BUILD.vcxproj
```

#### 2) Linux:
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
make
```

#### 3) macOS:
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
make
```

#### 4) iOS
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm64-ios -DVCPKG_CMAKE_SYSTEM_NAME=iOS -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 -DVCPKG_OSX_ARCHITECTURES=arm64
make
```

#### 5) Android
```shell
cd /path/to/project

# Build for ARM
mkdir build-arm
pushd build-arm
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm-android -DANDROID_ABI=armeabi-v7a -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/path/to/ndk/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles" 
/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe
popd

# Build for ARM64
mkdir build-arm64
pushd build-arm64
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm64-android -DANDROID_ABI=arm64-v8a -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/path/to/ndk/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe
popd

# Build for x86
mkdir build-x86
pushd build-x86
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=x86-android -DANDROID_ABI=x86 -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/path/to/ndk/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe
popd


# Build for x86_64
mkdir build-x86_64
pushd build-x86_64
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=x64-android -DANDROID_ABI=x86_64 -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/path/to/ndk/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
/path/to/ndk/prebuilt/windows-x86_64/bin/make.exe
popd
```

# License
[MIT](LICENSE)