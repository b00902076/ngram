# ngram
Japanese address search engine based on n-gram algorithm.<br>
Cross-platform supported including Linux ans Windows.

## Requirements
- For Linux:
  - Compiler: gcc 7.3.1 (Red-Hat)
  - Build-automation Tool: GNU Make 3.82
- For Windows 10:
  - Compiler: gcc 10.3.0 (MSYS2) (*1)
  - Build-automation Tool: GNU Make 4.3 (*2)
  - Shell: Powershell 7.1.4

## How to compile & run
On Linux:
```
$ make
$ ./ngram [-m=s|--mode=silent] [-s=h|--sort=hit] [-s=i|--sort=id]
```
Or `make run` for running without parameters.
<br><br>
On Windows:
```
$ make
$ ./ngram.exe [-m=s|--mode=silent] [-s=h|--sort=hit] [-s=i|--sort=id]
```
Still, `make run` for running without parameters.<br>
(or just double-click .exe file on the GUI)

## How it works
main algorithm: n-gram (n=2 by default)

(*1) Mingw g++ compiler(8.x.x) has bug in `fcntl.h`, which causes fatal error during compiling. [[ref](https://sourceforge.net/p/mingw-w64/bugs/737/)]

(*2) Setup by [chocolatey](https://chocolatey.org/install).