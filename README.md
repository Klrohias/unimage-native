# Unimage Native
Used by [Unimage Unity](https://github.com/Klrohias/unimage-unity).  
It can load `png`/`jpeg`/`webp`/`bmp`/`tga`/`gif` in to memory, and provides some simple operations.

# Building
### 1. Configure environment
```shell
export VCPKG_DIR=/path/to/vcpkg
export TRIPLET=... # triplet you want to build for

# If you want to build for Android:
export ANDROID_NDK_HOME=/path/to/ndk # set your android ndk path

# If it is the first time you build Unimage, add a new triplet to build with bitcode:
cp ./scripts/arm64-ios-bitcode.cmake $VCPKG_DIR/triplets/community/
```

<details><summary>Or you are using PowerShell</summary>
<p>
  
```shell
$VCPKG_DIR="/path/to/vcpkg"
$TRIPLET="..." # triplet you want to build for

# If you want to build for Android:
$ANDROID_NDK_HOME="/path/to/ndk" # set your android ndk path
$env:ANDROID_NDK_HOME=$ANDROID_NDK_HOME

#If it is the first time you build Unimage, add a new triplet to build with bitcode
cp ./scripts/arm64-ios-bitcode.cmake $VCPKG_DIR/triplets/community/
```
  
</p>
</details>

**If you want to build for iOS, you need to use triplet `arm64-ios-bitcode`**  

### 2. Install dependencies
```shell
pushd $TRIPLET
./vcpkg install "stb:$TRIPLET"
./vcpkg install "libwebp:$TRIPLET"
./vcpkg install "libjpeg-turbo:$TRIPLET"
popd
```

### 3. Generate for special platform:  
#### 1) Windows:
```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
msbuild ALL_BUILD.vcxproj
```

#### 2) Linux:
```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
make # or use ninja to build
```

#### 3) macOS:
```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
make
```

#### 4) iOS
```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm64-ios-bitcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64
make
```

#### 5) Android
```shell

# Build for ARM
mkdir build-arm
pushd build-arm
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm-android -DANDROID_ABI=armeabi-v7a -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles" 
$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe
popd

# Build for ARM64
mkdir build-arm64
pushd build-arm64
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm64-android -DANDROID_ABI=arm64-v8a -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe
popd

# Build for x86
mkdir build-x86
pushd build-x86
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=x86-android -DANDROID_ABI=x86 -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe
popd


# Build for x86_64
mkdir build-x86_64
pushd build-x86_64
cmake .. -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=x64-android -DANDROID_ABI=x86_64 -DVCPKG_CMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe -G "Unix Makefiles"
$ANDROID_NDK_HOME/prebuilt/windows-x86_64/bin/make.exe
popd
```

# License
[MIT](LICENSE)
