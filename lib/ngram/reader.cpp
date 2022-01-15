#include "reader.hpp"

Reader::Reader(string filename){
    #if defined(_WIN32) || defined(__WIN32__)
    ifs.open(filename);
    #elif __linux__
    wifs.open(filename);
    wifs.imbue(locale("C.UTF-8"));
    #endif
}

#if defined(_WIN32) || defined(__WIN32__)
ifstream& Reader::readLine(wstring& wline){
    getline(ifs, buffer);
    wline = converter.from_bytes(buffer.c_str());
    return ifs;
}
#elif __linux__
wifstream& Reader::readLine(wstring& wline){
    getline(wifs, wline);
    return wifs;
}
#endif

bool Reader::reachedEOF(){
    #if defined(_WIN32) || defined(__WIN32__)
    return ifs.eof();
    #elif __linux__
    return wifs.eof();
    #endif
}

bool Reader::successfullyRead(){
    #if defined(_WIN32) || defined(__WIN32__)
    return ifs.rdstate() == ios_base::goodbit;
    #elif __linux__
    return wifs.rdstate() == ios_base::goodbit;
    #endif
}

ios_base::iostate Reader::getIostate(){
    #if defined(_WIN32) || defined(__WIN32__)
    return ifs.rdstate();
    #elif __linux__
    return wifs.rdstate();
    #endif
}