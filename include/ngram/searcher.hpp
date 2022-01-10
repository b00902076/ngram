#ifndef NGRAM_INCLUDE_SEARCHER_H
#define NGRAM_INCLUDE_SEARCHER_H
#include "common.hpp"
#include "indexer.hpp"
#include "../../lib/ngram/config.hpp"
#include "../../lib/ngram/utils.hpp"
#include "../../lib/ngram/logger.hpp"

class Searcher {
    public:
        Searcher(Indexer& indexer);

    private:
        vector<wstring> records;
        Indexer& indexer;
        void loadRecord();
        void outputSearchResult(vector<pair<int,int>> &results);
        void search();
        Logger logger;
};
#endif
