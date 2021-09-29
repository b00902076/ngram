#ifndef NGRAM_COMPONENT_SEARCHER_H
#define NGRAM_COMPONENT_SEARCHER_H
#include "../../headers/common.hpp"
#include "../../config/config.hpp"
#include "../utils/utils.hpp"
#include "../logger/logger.hpp"
#include "../indexer/indexer.hpp"

class Searcher {
    public:
        Searcher(Indexer& indexer);
        void loadRecord();
        void outputSearchResult(vector<pair<int,int>> &results);
        void search();

    private:
        vector<wstring> records;
        Indexer& indexer;
};
#endif
