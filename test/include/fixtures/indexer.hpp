#ifndef NGRAM_TEST_INCLUDE_FIXTURE_INDEXER_HPP
#define NGRAM_TEST_INCLUDE_FIXTURE_INDEXER_HPP
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "../include/ngram/main.hpp"
#include "../utils/utils.hpp"
class IndexerTest: public testing::Test, public ngramTesting::Utils {
    protected:
    // Initialize without any flags
    void SetUp() override {
        Config config;
        config.test_mode = true;
        char *argv[1] = {"dummy.exe"};
        Initializer standard_mode(1, argv);
    }
    void TearDown() override {
        #if defined(_WIN32) || defined(__WIN32__)
        // redirect log stream(stdout) to handle output messages after Initializer executing _setmode()
        redirectTestLog(this);
        #endif
    }
};

#endif