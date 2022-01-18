#include "writter.hpp"

Writter::Writter(const string& filename): filename(filename){
    stream.open(filename, ios_base::binary);
    #if __linux__
    stream.imbue(locale("C.UTF-8"));
    #endif
}

Writter::Writter(const string& filename, ios_base::openmode mode): filename(filename){
    stream.open(filename, mode);
    #if __linux__
    stream.imbue(locale("C.UTF-8"));
    #endif
}

Writter& Writter::operator<<(const int& input){
    stream << input;
    return *this;
}

Writter& Writter::operator<<(const unsigned long& input){
    stream << input;
    return *this;
}

Writter& Writter::operator<<(const string& input){
    #if defined(_WIN32) || defined(__WIN32__)
    stream << input;
    #elif __linux__
    stream << converter.from_bytes(input.c_str());
    #endif
    return *this;
}

Writter& Writter::operator<<(const wstring& input){
    #if defined(_WIN32) || defined(__WIN32__)
    stream << converter.to_bytes(input);
    #elif __linux__
    stream << input;
    #endif
    return *this;
}

/**
 *  @brief Interface for manipulators such as @c Writter::endl .
 *  Acutal usage would be like "(Writter) << Writter::endl".
 */
Writter& Writter::operator<<(Writter& (*func)(Writter&)){
    return func(*this);
}

void Writter::flush(){
    stream.flush();
    return;
}

Writter& Writter::endl(Writter& _self){
    _self.stream << std::endl;
    return _self;
}

string Writter::getFilename(){
    return filename;
}
