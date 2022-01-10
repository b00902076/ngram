#ifndef NGRAM_INCLUDE_INDEXER_H
#define NGRAM_INCLUDE_INDEXER_H
#include "common.hpp"
#include "../../lib/ngram/reader.hpp"
#include "../../lib/ngram/logger.hpp"
#include "../../lib/ngram/writter.hpp"
#include "../../lib/ngram/utils.hpp"

class Indexer {
    public:
        Indexer();
        vector<vector<wstring>> csv;
        unordered_map<wstring, unordered_set<int>> index;
        
    private:
        void generateIndexFile();
        void buildIndex();
        void loadIndex();
        void generateConcatenedCsv();
        void mergePrevRecord(vector<wstring> &record, vector<int> target_columns);
        void loadCsv();
        Logger logger;
};
#endif
