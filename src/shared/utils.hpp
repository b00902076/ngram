#ifndef NGRAM_SRC_SHARED_UTILS_HPP
#define NGRAM_SRC_SHARED_UTILS_HPP
#include "../common/common.hpp"

class Utils {
    public:
    static bool availableKey(wstring &key, unordered_set<wchar_t> &skip_wc);
};
#endif
