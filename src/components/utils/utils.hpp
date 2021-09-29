#ifndef NGRAM_COMPONENT_UTILS_H
#define NGRAM_COMPONENT_UTILS_H
#include "../../headers/common.hpp"

class Utils {
    public:
    static bool availableKey(wstring &key, unordered_set<wchar_t> &skip_wc);
};
#endif
