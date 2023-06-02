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
cd path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg -DCMAKE_BUILD_TYPE=Release
msbuild ALL_BUILD.vcxproj
```

#### 2) Linux:
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg -DCMAKE_BUILD_TYPE=Release
make
```

#### 3) macOS:
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg -DCMAKE_BUILD_TYPE=Release
make
```

#### 4) iOS
```shell
cd /path/to/project
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=arm64-ios -DVCPKG_CMAKE_SYSTEM_NAME=iOS -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 -DVCPKG_OSX_ARCHITECTURES=arm64
make
```

# License
[MIT](LICENSE)