#include "../indexer.hpp"

void Indexer::generateIndexFile(){
    Writter FileWritter(_INDEX_PATH);

    for(auto &[key, values]:index){
        FileWritter << key;
        for(auto &doc_num:values)   FileWritter << L" " << doc_num;
        FileWritter << Writter::endl;
    }

    logger << L"Generated index file with " << int_size(index) << L" keys." << Logger::endl;
    return;
}

void Indexer::buildIndex(){
    vector<int> target_columns = {_CSV_COLUMN_INDEX_ADDRESS_1, _CSV_COLUMN_INDEX_ADDRESS_2, _CSV_COLUMN_INDEX_ADDRESS_3};
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～'};
    
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

    generateIndexFile();
    return;
}