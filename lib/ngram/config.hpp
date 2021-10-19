#ifndef NGRAM_LIB_NGRAM_CONFIG_HPP
#define NGRAM_LIB_NGRAM_CONFIG_HPP
#include <bits/stdc++.h>
#include <ngram/constants.hpp>

// TODO: maybe spilt config for indexer/searcher seperatedly?
class Config {
    public:
        static bool mute_stdout;
        static int sort_method;
        void resetAllConfigs();
};
#endif