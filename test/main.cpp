#include <gtest/gtest.h>
#include "ngram/config.hpp"
#include "ngram/indexer.hpp"
#include "ngram/utils.hpp"
#include "ngram/initializer.hpp"
#include "ngram/searcher.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}