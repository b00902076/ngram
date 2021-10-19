#include <gtest/gtest.h>
#include <ngram/main.hpp>
#include <fixtures/argument.hpp>
#include <fixtures/config.hpp>

// class Config

TEST_F(ConfigTest, DefaultValue) {
    config.resetAllConfigs();
    EXPECT_EQ(config.mute_stdout, false) << L"default config(mute_stdout) incorrect";
    EXPECT_EQ(config.sort_method, _SORT_METHOD_NULL) << L"default config(sort_method) incorrect";
}

// class Initializer

TEST_F(ArgumentTest, ConfigInitialization) {
    Config config;
    Initializer no_flag_init(no_flag_arg.argc, no_flag_arg.argv);
    EXPECT_EQ(config.mute_stdout, false) << L"config(mute_stdout) incorrect";
    EXPECT_EQ(config.sort_method, _SORT_METHOD_NULL) << L"config(sort_method) incorrect";
    
    struct Config_ {
        bool mute_stdout;
        int sort_method;
    };

    vector<Config_> expected_configs = {
        {true, _SORT_METHOD_NULL},{true, _SORT_METHOD_NULL},
        {false, _SORT_METHOD_BY_ID},{false, _SORT_METHOD_BY_ID},
        {false, _SORT_METHOD_BY_HITS},{false, _SORT_METHOD_BY_HITS}
    };
    EXPECT_EQ(int_size(expected_configs), int_size(single_flag_arg_set))
        << L"expected_configs and single_flag_arg_set having different length";
    
    for(int i=0; i<int_size(expected_configs); i++){
        config.resetAllConfigs();
        Initializer single_flag_init(single_flag_arg_set[i].argc, single_flag_arg_set[i].argv);
        auto [expected_mute_stdout, expected_sort_method] = expected_configs[i];
        EXPECT_EQ(config.mute_stdout, expected_mute_stdout) << L"config(mute_stdout) incorrect";
        EXPECT_EQ(config.sort_method, expected_sort_method) << L"config(sort_method) incorrect";
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}