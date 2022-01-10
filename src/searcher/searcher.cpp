#include <ngram/searcher.hpp>
#include "methods/load_record.cc"
#include "methods/search.cc"

Searcher::Searcher(Indexer& indexer): indexer(indexer), logger(Config::test_mode? _LOG_PATH_TEST:_LOG_PATH) {
    // load concatened records for quick output
    loadRecord();
    // perform search
    search();
}
