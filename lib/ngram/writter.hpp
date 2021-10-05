#ifndef NGRAM_LIB_NGRAM_WRITTER_H
#define NGRAM_LIB_NGRAM_WRITTER_H
#include "../../include/common.hpp"

class Writter {
    public:
        Writter(const string& filename);
        Writter(const string& filename, ios_base::openmode mode);
        Writter& operator<<(const int& input);
        Writter& operator<<(const unsigned long& input);
        Writter& operator<<(const string& input);
        Writter& operator<<(const wstring& input);
        Writter& operator<<(Writter& (*func)(Writter&));
        void flush();
        static Writter& endl(Writter&);

    protected:
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        
        #if defined(_WIN32) || defined(__WIN32__)
        ofstream stream;

        #elif __linux__
        wofstream stream;
        #endif
};
#endif
