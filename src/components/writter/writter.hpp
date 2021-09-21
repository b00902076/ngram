#include "../../headers/common.hpp"

class Writter {
    public:
    Writter(const string& filename);
    Writter& operator<<(const int& num);
    Writter& operator<<(const wstring& ws);
    void flush();
    Writter& endl();

    private:
    #if defined(_WIN32) || defined(__WIN32__)
    ofstream ofs;
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    #elif __linux__
    wofstream wofs;
    #endif
};