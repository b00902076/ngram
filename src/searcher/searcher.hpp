#ifndef NGRAM_SRC_SEARCHER_SEARCHER_HPP
#define NGRAM_SRC_SEARCHER_SEARCHER_HPP
#include "../common/common.hpp"
#include "../indexer/indexer.hpp"
#include "../shared/config.hpp"
#include "../shared/utils.hpp"
#include "../shared/logger.hpp"
#include "../shared/query_fetcher.hpp"

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
        unordered_set<wchar_t> skip_wc;
        wstring guide_message;
};
#endif
