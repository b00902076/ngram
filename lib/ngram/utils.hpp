#ifndef NGRAM_LIB_NGRAM_UTILS_H
#define NGRAM_LIB_NGRAM_UTILS_H
#include "../../include/common.hpp"

class Utils {
    public:
    static bool availableKey(wstring &key, unordered_set<wchar_t> &skip_wc);
};
#endif
