#include "common.h"

// store index content as file
// output encoding: shift-jis
void generate_index_file(unordered_map<wstring, unordered_set<int>> &index){
    wofstream index_file(_INDEX_FILENAME);
    for(auto &[key, values]:index){
        index_file << key << L" ";
        int sz=values.size(), i=0;
        for(auto &row_pos:values){
            index_file << row_pos;
            if(i<sz-1)  index_file << L" ";
            else        index_file << endl;
            i++;
        }
    }
    wcout << L"Generated index file with " << index.size() << L" keys." << endl;
    index_file.close();
    return;
}

void build_index(vector<vector<wstring>> &csv){
    vector<int> target_columns = {_CSV_COLUMN_INDEX_ADDRESS_1, _CSV_COLUMN_INDEX_ADDRESS_2, _CSV_COLUMN_INDEX_ADDRESS_3};
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～'};
    unordered_map<wstring, unordered_set<int>> index;
    
    // build n-gram index row by row
    for(int row_pos=0; row_pos<csv.size(); row_pos++){
        vector<wstring> &row = csv[row_pos];
        for(auto &col_pos:target_columns){
            wstring &col = row[col_pos];
            for(int i=1; i<col.size()-N; i++){
                wstring key = col.substr(i,N);
                if(avalible_key(key, skip_wc))  index[key].emplace(row_pos);
            }
        }
    }

    generate_index_file(index);
    return;
}
