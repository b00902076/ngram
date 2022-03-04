#ifndef NGRAM_SRC_INDEXER_INDEXER_HPP
#define NGRAM_SRC_INDEXER_INDEXER_HPP
#include "../common/common.hpp"
#include "../shared/reader.hpp"
#include "../shared/logger.hpp"
#include "../shared/writter.hpp"
#include "../shared/utils.hpp"

class Indexer {
    public:
        Indexer();
        void loadCsv();
        void buildIndex();
        void loadIndex();
        vector<vector<wstring>> csv;
        unordered_map<wstring, unordered_set<int>> index;
        
    private:
        void generateIndexFile();
        void generateConcatenedCsv();
        void mergePrevRecord(vector<wstring> &record, vector<int> target_columns);
        Logger logger;
};
#endif
