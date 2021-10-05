#ifndef NGRAM_INCLUDE_INDEXER_H
#define NGRAM_INCLUDE_INDEXER_H
#include "common.hpp"
#include "../lib/ngram/reader.hpp"
#include "../lib/ngram/logger.hpp"
#include "../lib/ngram/writter.hpp"
#include "../lib/ngram/utils.hpp"

class Indexer {
    public:
        Indexer();
        unordered_map<wstring, unordered_set<int>> index;
        
    private:
        vector<vector<wstring>> csv;
        // TODO: name refactor
        void generateIndexFile();
        void buildIndex();
        void loadIndex();
        void generateConcatenedCsv();
        void mergePrevRecord(vector<wstring> &record, vector<int> target_columns);
        void loadCsv();
        Logger logger;
};
#endif
