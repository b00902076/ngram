#ifndef NGRAM_TEST_NGRAM_CONFIG_HPP
#define NGRAM_TEST_NGRAM_CONFIG_HPP
#include <gtest/gtest.h>
#include "../../src/common/common.hpp"
#include "../include/fixtures/config.hpp"
// class Config
TEST_F(ConfigTest, DefaultValue){
    config.resetAllConfigs();
    EXPECT_EQ(config.mute_stdout, false) << L"default config(mute_stdout) incorrect";
    EXPECT_EQ(config.sort_method, _SORT_METHOD_NULL) << L"default config(sort_method) incorrect";
    EXPECT_EQ(config.test_mode, false) << L"default config(test_mode) incorrect";
}
#endif