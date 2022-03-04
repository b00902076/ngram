#ifndef NGRAM_TEST_INCLUDE_FIXTURES_INDEXER_HPP
#define NGRAM_TEST_INCLUDE_FIXTURES_INDEXER_HPP
#include <gtest/gtest.h>
#include "../../../src/main.hpp"
#include "../utils/utils.hpp"
class IndexerTest: public testing::Test, public ngramTesting::Utils {
    protected:
    // Initialize without any flags
    void SetUp() override {
        Config config;
        config.test_mode = true;
        char *argv[1] = {(char *)"dummy.exe"};
        Initializer standard_mode(sizeof(argv)/sizeof(char *), argv);
        redirectTestLog(this);
    }
    void TearDown() override {
        handleErrorOutput(this);
    }
};

#endif