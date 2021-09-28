#include "headers/build_index.hpp"
#include "components/logger/logger.hpp"
#include "components/utils/utils.hpp"

// store index content as file
void generate_index_file(unordered_map<wstring, unordered_set<int>> &index){
    Writter FileWritter(_INDEX_PATH);
    Logger logger(_LOG_PATH);

    for(auto &[key, values]:index){
        FileWritter << key;
        for(auto &doc_num:values)   FileWritter << L" " << doc_num;
        FileWritter << Writter::endl;
    }

    logger << L"Generated index file with " << int_size(index) << L" keys." << Logger::endl;
    return;
}

void build_index(vector<vector<wstring>> &csv){
    vector<int> target_columns = {_CSV_COLUMN_INDEX_ADDRESS_1, _CSV_COLUMN_INDEX_ADDRESS_2, _CSV_COLUMN_INDEX_ADDRESS_3};
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～'};
    unordered_map<wstring, unordered_set<int>> index;
    
    // build n-gram index row by row
    for(int row_pos=0; row_pos<int_size(csv); row_pos++){
        vector<wstring> &row = csv[row_pos];
        for(auto &col_pos:target_columns){
            wstring &col = row[col_pos];
            for(int i=1; i<int_size(col)-_N_GRAM_LENGTH; i++){
                wstring key = col.substr(i,_N_GRAM_LENGTH);
                if(Utils::availableKey(key, skip_wc))  index[key].emplace(row_pos);
            }
        }
    }

    generate_index_file(index);
    return;
}