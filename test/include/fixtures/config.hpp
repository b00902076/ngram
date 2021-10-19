#ifndef NGRAM_TEST_INCLUDE_FIXTURES_CONFIG_HPP
#define NGRAM_TEST_INCLUDE_FIXTURES_CONFIG_HPP
#include <gtest/gtest.h>
#include "../../../lib/ngram/config.hpp"

class ConfigTest: public ::testing::Test {
    protected:
        void SetUp() override {}

        Config config;
};
#endif
