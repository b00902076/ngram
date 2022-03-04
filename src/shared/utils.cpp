#include "utils.hpp"

// check if key contains any character should be considered to skip
bool Utils::availableKey(wstring &key, unordered_set<wchar_t> &skip_wc){
    for(auto &wc:key){
        if(skip_wc.count(wc)>0)  return false;
    }
    return true;
}