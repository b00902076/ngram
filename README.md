# ngram
Japanese address search engine based on n-gram algorithm.<br>
Cross-platform supported including Linux and Windows.

## Prerequisite
- For Linux:
  - Compiler: `gcc 7.3.1`
  - Build-automation Tool: `CMake` & `GNU Make`
  - `Openssl` (for `CMake` dependency)
- For Windows 10(64-bit):
  - Compiler: `gcc 10.3.0 (MSYS2)` (*1)
  - Build-automation Tool: `CMake` & `GNU Make` (*2)
  - `Openssl` (for `CMake` dependency)

## Setup Project
```
$ git submodule init
$ git submodule update
```
(for setup dev-tools)

## Setup Openssl on Linux
CentOS, Amazon linux 2:
```
$ sudo yum install openssl-devel
```
Ubuntu:
```
$ sudo apt-get install libssl-dev
```

## Setup CMake on Linux
Visit [CMake official site](https://cmake.org/download/) to get download link:
```
$ wget <download-link>
$ tar zxvf <downloaded-tar-file>
$ cd <cmake-dir>
$ sudo ./bootstrap
$ sudo make
$ sudo make install
```
Clean up:
```
$ sudo rm -rf <cmake-dir> <downloaded-tar-file>
```

## How to Build
On Linux:
```
$ cmake -B build -S .
$ cd build && cmake --build .
```
On Windows:
```
$ cmake -G "Unix Makefiles" -B build -S .
$ cmake --build build
```

## How to Run
By `make`:
```
$ make run
```
Or `make run/fast` to avoid reproccessing.<br><br>
From binary:
```
$ ./bin/ngram.exe [-m=s|--mode=silent] [-s=h|--sort=hit] [-s=i|--sort=id]
```

## How to Test
(under `<project>/build` directory)
```
$ ctest
```
On windows platform, messages output by gtest will be redirected to `build/test_result[w].log` after initializer execute `_setmode()`.

## How it works
main algorithm: n-gram (n=2 by default)

(*1) Mingw g++ compiler(8.x.x) has bug in `fcntl.h`, which causes fatal error during compiling. [[ref](https://sourceforge.net/p/mingw-w64/bugs/737/)]

(*2) GNU Make could setup by [chocolatey](https://chocolatey.org/install).