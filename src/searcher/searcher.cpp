#include <ngram/searcher.hpp>
#include "methods/load_record.cc"
#include "methods/search.cc"

Searcher::Searcher(Indexer& indexer): indexer(indexer){
    // load concatened records for quick output
    loadRecord();
    // perform search
    search();
}
