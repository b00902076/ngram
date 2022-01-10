#include <ngram/indexer.hpp>
#include "methods/build_index.cc"
#include "methods/load_csv.cc"
#include "methods/load_index.cc"

Indexer::Indexer(): logger(Config::test_mode? _LOG_PATH_TEST:_LOG_PATH) {
    // load source file and perform concatenation
    // TODO: seperate loading & concatenating part
    loadCsv();
    // build index and store at local
    buildIndex();
    // load index file from the generated one
    loadIndex();
}


