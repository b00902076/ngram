#ifndef NGRAM_INCLUDE_SEARCHER_H
#define NGRAM_INCLUDE_SEARCHER_H
#include "common.hpp"
#include "indexer.hpp"
#include "../../lib/ngram/config.hpp"
#include "../../lib/ngram/utils.hpp"
#include "../../lib/ngram/logger.hpp"
#include "../../lib/ngram/query_fetcher.hpp"

class Searcher {
    public:
        Searcher(Indexer& indexer);
        void loadRecord();
        void search();
        int proccessOneQuery(wstring &query, Indexer &indexer);

    private:
        vector<wstring> records;
        Indexer& indexer;
        void outputSearchResult(vector<pair<int,int>> &results);
        void handleErrorWIN32();
        Logger logger, error_logger;
        QueryFetcher query_fetcher;
        Writter result_writter;
        unordered_set<wchar_t> skip_wc;
        wstring guide_message;
};
#endif
