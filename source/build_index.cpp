#include "headers/build_index.hpp"
#include "components/utils/utils.hpp"

// store index content as file
void generate_index_file(unordered_map<wstring, unordered_set<int>> &index){
    #if defined(_WIN32) || defined(__WIN32__)
    ofstream index_file(_INDEX_PATH, ios_base::binary);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    char space=' ', new_line='\n';
    #elif __linux__
    wofstream index_file(_INDEX_PATH, ios_base::binary);
    index_file.imbue(locale("C.UTF-8"));
    wchar_t space=L' ', new_line=L'\n';
    #endif

    for(auto &[key, values]:index){
        index_file
        #if defined(_WIN32) || defined(__WIN32__)
            << converter.to_bytes(key)
        #elif __linux__
            << key
        #endif
            << space;
        int i=0;
        for(auto &doc:values){
            index_file << doc << (i==int_size(values)-1? new_line:space);
            i++;
        }
    }
    wcout << L"Generated index file with " << int_size(index) << L" keys." << endl;
    index_file.close();
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
                if(Utils::avalible_key(key, skip_wc))  index[key].emplace(row_pos);
            }
        }
    }

    generate_index_file(index);
    return;
}