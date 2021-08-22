# ngram
Japanese address search engine based on n-gram algorithm

## Environment & Requirement
- OS: Windows 10
- Compiler: gcc version 9.0.0+

## How to compile
```
$ cd .\source
$ g++ .\load_csv.cpp .\build_index.cpp .\main.cpp .\load_record.cpp .\load_index.cpp .\search.cpp .\utils.cpp -o main.exe
```

## How to run
```
$ .\main.exe
```
or just double-click .exe file on the GUI

## How it works
main algorithm: n-gram (n=2 by default)
