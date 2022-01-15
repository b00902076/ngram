#ifndef NGRAM_LIB_NGRAM_READER_HPP
#define NGRAM_LIB_NGRAM_READER_HPP
#include "../../include/ngram/common.hpp"

class Reader {
    public:
    Reader(string filename);
    #if defined(_WIN32) || defined(__WIN32__)
    ifstream& readLine(wstring& wline);
    #elif __linux__
    wifstream& readLine(wstring& wline);
    #endif
    bool reachedEOF();
    bool successfullyRead();
    ios_base::iostate getIostate();

    private:
    #if defined(_WIN32) || defined(__WIN32__)
    ifstream ifs;
    // TODO: use ICU(or maybe boost) to convert utf8 string to wstring.
    // Note: The header <codecvt> is unrecommand since c++17 due to the ambiguous implementation,
    // and its improper error handling when reading file in unexpected code point.
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string buffer;
    #elif __linux__
    wifstream wifs;

    #endif
};
#endif
