#ifndef NGRAM_TEST_INCLUDE_FIXTURES_CONFIG_HPP
#define NGRAM_TEST_INCLUDE_FIXTURES_CONFIG_HPP
#include <gtest/gtest.h>
#include "../../../lib/ngram/config.hpp"
#include "../utils/utils.hpp"
class ConfigTest: public ::testing::Test, public ngramTesting::Utils {
    protected:
        void SetUp() override {
            redirectTestLog(this);
        }
        void TearDown() override {
            handleErrorOutput(this);
        }

        Config config;
};
#endif
