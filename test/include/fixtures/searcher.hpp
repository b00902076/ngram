#ifndef NGRAM_TEST_INCLUDE_FIXTURES_SEARCHER_HPP
#define NGRAM_TEST_INCLUDE_FIXTURES_SEARCHER_HPP
#include <gtest/gtest.h>
#include "../../../src/main.hpp"
#include "../utils/utils.hpp"
class SearcherTest: public testing::Test, public ngramTesting::Utils {
    protected:
    void SetUp() override {
        Config config;
        config.test_mode = true;
        Initializer standard_mode(sizeof(argv)/sizeof(char *), argv);
        redirectTestLog(this);
        indexer.loadIndex();
    }
    void TearDown() override {
        handleErrorOutput(this);
    }
    // TODO: Survey: Logger crashes when perform wcout after redirection.
    // Note: Output <string> looks great but <wstring> will fail.
    char *argv[2] = {(char *)"dummy.exe", (char *)"--mode=silent"};
    Indexer indexer;
};

#endif