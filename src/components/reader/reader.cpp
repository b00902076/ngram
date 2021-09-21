#include "reader.hpp"

#if defined(_WIN32) || defined(__WIN32__)
Reader::Reader(string filename){
    ifs.open(filename);
}
ifstream& Reader::readLine(wstring& wline){
    getline(ifs, buffer);
    wline = converter.from_bytes(buffer.c_str());
    return ifs;
}
#elif __linux__
Reader::Reader(string filename){
    wifs.open(filename);
    wifs.imbue(locale("C.UTF-8"));
}
wifstream& Reader::readLine(wstring& wline){
    getline(wifs, wline);
    return wifs;
}
#endif