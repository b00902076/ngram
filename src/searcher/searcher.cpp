#include "../../include/ngram/searcher.hpp"
#include "../../lib/ngram/query_fetcher.hpp"
#include "methods/load_record.cc"
#include "methods/search.cc"

Searcher::Searcher(Indexer& indexer): indexer(indexer), logger(Config::test_mode? _LOG_PATH_TEST:_LOG_PATH) {
    
}
