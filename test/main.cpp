#include <gtest/gtest.h>
#include "../include/ngram/main.hpp"
#include "fixtures/argument.hpp"
#include "fixtures/config.hpp"
#include "fixtures/indexer.hpp"
#include "fixtures/utils_available_key.hpp"

// class Config
TEST_F(ConfigTest, DefaultValue){
    config.resetAllConfigs();
    EXPECT_EQ(config.mute_stdout, false) << L"default config(mute_stdout) incorrect";
    EXPECT_EQ(config.sort_method, _SORT_METHOD_NULL) << L"default config(sort_method) incorrect";
    EXPECT_EQ(config.test_mode, false) << L"default config(test_mode) incorrect";
}

// class Initializer
TEST_F(ArgumentTest, ConfigInitialization){
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

// class Utils
TEST(UtilsTest, availableKey){
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
    vector<wstring> good_keys = {L"北海道", L"東京都", L"大阪"};
    vector<wstring> bad_keys = {L"北海道、", L"（東京都", L"大阪）", L"京都　府", L"京 都", L"１２３～１３０"};
    for(auto &good_key:good_keys){
        EXPECT_TRUE(Utils::availableKey(good_key, skip_wc));
    }
    for(auto &bad_key:bad_keys){
        EXPECT_FALSE(Utils::availableKey(bad_key, skip_wc));
    }
}

// Another approach: testing with parameters
TEST_P(UtilsAvailablekeyTest, goodKeys){
    auto good_key = GetParam();
    EXPECT_TRUE(Utils::availableKey(good_key, skip_wc));
}
TEST_P(UtilsAvailablekeyTest2, badKeys){
    auto bad_key = GetParam();
    EXPECT_FALSE(Utils::availableKey(bad_key, skip_wc));
}
INSTANTIATE_TEST_CASE_P(
    TestByParams,
    UtilsAvailablekeyTest,
    ::testing::ValuesIn(vector<wstring>{L"北海道", L"東京都", L"大阪"})
);
INSTANTIATE_TEST_CASE_P(
    TestByParams2,
    UtilsAvailablekeyTest2,
    ::testing::ValuesIn(vector<wstring>{L"北海道、", L"（東京都", L"大阪）", L"京都　府", L"京 都", L"１２３～１３０"})
);

// class indexer
TEST_F(IndexerTest, Indexer){
    Indexer indexer;
    EXPECT_EQ(indexer.csv.size(), 124223) << L"Concatened csv is not correct";
    EXPECT_EQ(indexer.index.size(), 54855) << L"Index loaded is not correct";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}