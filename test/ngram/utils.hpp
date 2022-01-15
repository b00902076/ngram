#ifndef NGRAM_TEST_NGRAM_UTILS_HPP
#define NGRAM_TEST_NGRAM_UTILS_HPP
#include <gtest/gtest.h>
#include "../../lib/ngram/utils.hpp"
#include "../include/fixtures/utils_available_key.hpp"
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
// TEST_P(UtilsAvailablekeyTest, goodKeys){
//     auto good_key = GetParam();
//     EXPECT_TRUE(Utils::availableKey(good_key, skip_wc));
// }
// TEST_P(UtilsAvailablekeyTest2, badKeys){
//     auto bad_key = GetParam();
//     EXPECT_FALSE(Utils::availableKey(bad_key, skip_wc));
// }
// INSTANTIATE_TEST_CASE_P(
//     TestByParams,
//     UtilsAvailablekeyTest,
//     ::testing::ValuesIn(vector<wstring>{L"北海道", L"東京都", L"大阪"})
// );
// INSTANTIATE_TEST_CASE_P(
//     TestByParams2,
//     UtilsAvailablekeyTest2,
//     ::testing::ValuesIn(vector<wstring>{L"北海道、", L"（東京都", L"大阪）", L"京都　府", L"京 都", L"１２３～１３０"})
// );
#endif
