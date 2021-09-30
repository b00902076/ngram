#ifndef NGRAM_COMPONENT_INDEXER_H
#define NGRAM_COMPONENT_INDEXER_H
#include "../../headers/common.hpp"
#include "../reader/reader.hpp"
#include "../logger/logger.hpp"
#include "../writter/writter.hpp"
#include "../utils/utils.hpp"

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
