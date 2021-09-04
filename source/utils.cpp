#include "headers/common.hpp"

// check if key contains any character should be considered to skip
bool avalible_key(wstring &key, unordered_set<wchar_t> &skip_wc){
    for(auto &wc:key){
        if(skip_wc.count(wc)>0)  return false;
    }
    return true;
}