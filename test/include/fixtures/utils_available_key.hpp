#ifndef NGRAM_TEST_INCLUDE_FIXTURES_UTILS_AVAILABLE_KEY_HPP
#define NGRAM_TEST_INCLUDE_FIXTURES_UTILS_AVAILABLE_KEY_HPP
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
class UtilsAvailablekeyTest: public ::testing::TestWithParam<wstring> {
    protected:
        unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
};
class UtilsAvailablekeyTest2: public ::testing::TestWithParam<wstring> {
    protected:
        unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
};
#endif