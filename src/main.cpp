#include <ngram/main.hpp>
// constrains:
// - source file with utf-8 encoding, LF as new line

int main(int argc, char *argv[]){
    // TODO: add excuting time measure
    Initializer initializer(argc, argv);
    Indexer indexer;
    Searcher searcher(indexer);

    return 0;
}