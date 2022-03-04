#include "indexer.hpp"
#include "methods/build_index.cc"
#include "methods/load_csv.cc"
#include "methods/load_index.cc"

Indexer::Indexer(): logger(Config::test_mode? _LOG_PATH_TEST:_LOG_PATH) {

}
