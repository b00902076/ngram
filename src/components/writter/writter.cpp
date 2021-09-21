#include "writter.hpp"

Writter::Writter(const string& filename){
    #if defined(_WIN32) || defined(__WIN32__)
    ofs.open(filename, ios_base::binary);
    #elif __linux__
    wofs.open(filename, ios_base::binary);
    wofs.imbue(locale("C.UTF-8"));
    #endif
}

Writter& Writter::operator<<(const wstring& ws){
    #if defined(_WIN32) || defined(__WIN32__)
    ofs << converter.to_bytes(ws);
    #elif __linux__
    wofs << ws;
    #endif
    return *this;
}

Writter& Writter::operator<<(const int& num){
    #if defined(_WIN32) || defined(__WIN32__)
    ofs << num;
    #elif __linux__
    wofs << num;
    #endif
    return *this;
}

void Writter::flush(){
    #if defined(_WIN32) || defined(__WIN32__)
    ofs.flush();
    #elif __linux__
    wofs.flush();
    #endif
    return;
}

Writter& Writter::endl(){
    #if defined(_WIN32) || defined(__WIN32__)
    ofs << std::endl;
    #elif __linux__
    wofs << std::endl;
    #endif
    return *this;
}
