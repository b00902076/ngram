#ifndef NGRAM_TEST_NGRAM_INDEXER_HPP
#define NGRAM_TEST_NGRAM_INDEXER_HPP
#include <gtest/gtest.h>
#include "../../include/ngram/indexer.hpp"
#include "../include/fixtures/indexer.hpp"
// class indexer
TEST_F(IndexerTest, AllFeatures){
    Indexer indexer;
    // test concatened csv
    EXPECT_EQ(indexer.csv.size(), 124223) << L"CSV(runtime variable) is not correct";
    ifstream csv(_CSV_CONCATENED_PATH_TEST);
    int csv_line_cnt = std::count(std::istreambuf_iterator<char>(csv), std::istreambuf_iterator<char>(), '\n');
    EXPECT_EQ(csv_line_cnt, 124223) << L"CSV doesn't have expected lines.";
    csv.close();

    // test index file
    EXPECT_EQ(indexer.index.size(), 54855) << L"Index loaded(runtime variable) is not correct";
    ifstream index(_INDEX_PATH_TEST);
    int index_line_cnt = std::count(std::istreambuf_iterator<char>(index), std::istreambuf_iterator<char>(), '\n');
    EXPECT_EQ(index_line_cnt, 54855) << L"Index file doesn't have expected lines.";
    index.close();
}
#endif
