# ngram
Japanese address search engine based on n-gram algorithm

## Environment & Requirement
- OS: Linux / Windows 10
- Compiler
  - Linux: gcc 7.3.1-13 (Red-Hat)
  - Windows: gcc 9.0.0+ (Mingw) (*1)

## How to compile
On Linux:
```
$ cd ./source
$ g++ ./load_csv.cpp ./build_index.cpp ./main.cpp ./load_record.cpp ./load_index.cpp ./search.cpp ./utils.cpp -o main.exe -std=c++17
```
On Windows:
```
$ cd .\source
$ g++ .\load_csv.cpp .\build_index.cpp .\main.cpp .\load_record.cpp .\load_index.cpp .\search.cpp .\utils.cpp -o main.exe -std=c++17
```

## How to run
On Linux:
```
$ ./main.exe [-m=s | --mode=silent] [-s=h | --sort=hit] [-s=i | --sort=id]
```
On Windows:
```
$ .\main.exe [-m=s | --mode=silent] [-s=h | --sort=hit] [-s=i | --sort=id]
```
(or just double-click .exe file on the GUI)

## How it works
main algorithm: n-gram (n=2 by default)

(*1) Mingw g++ compiler(8.x.x) has bug in `fcntl.h`, which causes fatal error during compiling.<br>
ref: https://sourceforge.net/p/mingw-w64/bugs/737/
