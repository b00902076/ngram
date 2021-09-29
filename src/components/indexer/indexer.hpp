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
        // TODO: name refactor
        void generate_index_file();
        void build_index();
        void load_index();
        void generate_concatened_csv();
        void merge_prev_record(vector<wstring> &record, vector<int> target_columns);
        void load_csv();
        unordered_map<wstring, unordered_set<int>> index;
        
    private:
        vector<vector<wstring>> csv;
};
#endif
