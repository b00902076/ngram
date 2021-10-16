#include <ngram/main.hpp>
#include <gtest/gtest.h>
// #include "lib/ngram/config.hpp"
// #include <lib/ngram/initializer.hpp>

// Config

TEST(ConfigTest, DefaultValue) {
    Config config;
    char ** mock_argv = nullptr;
    Initializer initializer(0, mock_argv);
    EXPECT_EQ(config.mute_stdout, false) << L"default config(mute_stdout) incorrect";
    EXPECT_EQ(config.sort_method, 0) << L"default config(sort_method) incorrect";
}