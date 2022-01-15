#include "../include/ngram/main.hpp"
// constrains:
// - source file with utf-8 encoding, LF as new line

int main(int argc, char *argv[]){
    // TODO: add excuting time measure
    Initializer initializer(argc, argv);
    Indexer indexer;
    // load source file and perform concatenation
    // TODO: seperate loading & concatenating part
    indexer.loadCsv();
    // build index and store at local
    indexer.buildIndex();
    // load index file from the generated one
    indexer.loadIndex();

    // TODO: refactor: searcher/indexer should be independent
    Searcher searcher(indexer);
    // load concatened records for quick output
    searcher.loadRecord();
    // perform search
    searcher.search();

    return 0;
}