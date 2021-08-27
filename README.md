# ngram
Japanese address search engine based on n-gram algorithm

## Environment & Requirement
- OS: linux

## How to compile
```
$ cd ./source
$ g++ ./load_csv.cpp ./build_index.cpp ./main.cpp ./load_record.cpp ./load_index.cpp ./search.cpp ./utils.cpp -o main.exe -std=c++17
```

## How to run
```
$ ./main.exe
```

## How it works
main algorithm: n-gram (n=2 by default)

(*1) g++ compiler(8.x.x) has bug with `fcntl.h`.
ref: https://sourceforge.net/p/mingw-w64/bugs/737/