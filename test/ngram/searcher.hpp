#ifndef NGRAM_TEST_NGRAM_SEARCHER_HPP
#define NGRAM_TEST_NGRAM_SEARCHER_HPP
#include <gtest/gtest.h>
#include "../../src/indexer/indexer.hpp"
#include "../../src/searcher/searcher.hpp"
#include "../include/fixtures/searcher.hpp"
#include "../include/utils/constants.hpp"

// class searcher
TEST_F(SearcherTest, Overall){
    Searcher searcher(indexer);
    // Notice: two file should contain same line counts.
    QueryFetcher query_fetcher(_TEST_SEARCH_QUERY_PATH);
    Reader expected_result_reader(_TEST_SEARCH_EXPECTED_RESULT_PATH);
    searcher.loadRecord();
    wstring query;

    while(query_fetcher.fetchOneQuery(query)){
        wstring expected_cnt_wstr;
        expected_result_reader.readLine(expected_cnt_wstr);
        int expected_cnt = stoi(expected_cnt_wstr);
        int actual_cnt = searcher.proccessOneQuery(query, indexer);
        EXPECT_EQ(expected_cnt, actual_cnt)
            << L"Search result(runtime variable) incorrect.";
        ifstream search_result(_TEST_SEARCH_RESULT_PATH);
        int actual_result_file_line_cnt = std::count(std::istreambuf_iterator<char>(search_result), std::istreambuf_iterator<char>(), '\n');
        EXPECT_EQ(expected_cnt, actual_result_file_line_cnt)
            << L"Search result file doesn't have expected line counts.";
    }
}
#endif
