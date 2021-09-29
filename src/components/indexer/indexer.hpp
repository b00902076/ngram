#pragma once
#include "../../headers/common.hpp"
#include "../../headers/constants.hpp"
#include "../reader/reader.hpp"
#include "../logger/logger.hpp"
#include "../utils/utils.hpp"

class Indexer {
    public:
        Indexer();
        void generate_index_file();
        void build_index();
        void load_index();
        void generate_concatened_csv();
        void merge_prev_record(vector<wstring> &record, vector<int> target_columns);
        void load_csv();
        void load_record();
        vector<vector<wstring>> csv;
        vector<wstring> records;
        unordered_map<wstring, unordered_set<int>> index;
        
    private:
};