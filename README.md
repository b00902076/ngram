# ngram
Japanese address search engine based on n-gram algorithm.<br>
Supported on both Linux and Windows platform.

## Requirements
- OS: Linux / Windows 10
- Compiler
  - Linux: gcc 7.3.1 (Red-Hat)
  - Windows: gcc 9.0.0+ (Mingw) (*1)

## How to compile & run
On Linux:
```
$ cd ./source
$ make
$ ./ngram [-m=s|--mode=silent] [-s=h|--sort=hit] [-s=i|--sort=id]
```
On Windows:
```
$ cd .\source
$ g++ .\load_csv.cpp .\build_index.cpp .\main.cpp .\load_record.cpp .\load_index.cpp .\search.cpp .\components\utils\utils.cpp .\components\reader\reader.cpp -o ngram.exe -std=c++17 -Wall
$ .\ngram.exe [-m=s|--mode=silent] [-s=h|--sort=hit] [-s=i|--sort=id]
```
(or just double-click .exe file on the GUI)

## How it works
main algorithm: n-gram (n=2 by default)

(*1) Mingw g++ compiler(8.x.x) has bug in `fcntl.h`, which causes fatal error during compiling.<br>
ref: https://sourceforge.net/p/mingw-w64/bugs/737/
