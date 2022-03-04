#ifndef NGRAM_SRC_SHARED_CONFIG_HPP
#define NGRAM_SRC_SHARED_CONFIG_HPP
#include <bits/stdc++.h>
#include "../common/constants.hpp"

// TODO: maybe spilt config for indexer/searcher seperatedly?
class Config {
    public:
        static bool test_mode;
        static bool mute_stdout;
        static int sort_method;
        static bool fetch_query_from_stdin;
        void resetAllConfigs();
};
#endif