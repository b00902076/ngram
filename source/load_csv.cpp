#include "headers/load_csv.hpp"
#include "headers/constants.hpp"

void generate_concatened_csv(vector<vector<wstring>> &csv){
    #if defined(_WIN32) || defined(__WIN32__)
    ofstream concatened_csv(_CSV_CONCATENED_PATH, ios_base::binary);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    for(auto &row:csv){
        for(int i=0; i<int_size(row); i++){
            concatened_csv << converter.to_bytes(row[i]) << (i==int_size(row)-1? '\n':',');
        }
    }
    #elif __linux__
    wofstream concatened_csv(_CSV_CONCATENED_PATH);
    concatened_csv.imbue(locale("C.UTF-8"));
    for(auto &row:csv){
        for(int i=0; i<int_size(row); i++){
            concatened_csv << row[i] << (i==int_size(row)-1? L'\n':L',');
        }
    }
    #endif
    concatened_csv.close();
    return;
}

void merge_prev_record(vector<vector<wstring>> &csv, vector<wstring> &record, vector<int> target_columns){
    wstring prev, current;
    for(auto &col:target_columns){
        prev = csv.back()[col];
        current = record[col];
        csv.back()[col] = prev.substr(0, int_size(prev)-1) + current.substr(1, int_size(current)-1);
    }
    return;
}

void load_csv(vector<vector<wstring>> &csv){
    bool between_parentheses=false, merge_mode=false;
    wchar_t delim=L',', left_p=L'（', right_p=L'）';
    wstring wline, cell=L"";
    vector<wstring> record;

    #if defined(_WIN32) || defined(__WIN32__)
    ifstream source_csv(_CSV_SOURCE_PATH);
    // TODO: use ICU(or maybe boost) to convert utf8 string to wstring.
    // Note: The header <codecvt> is unrecommand since c++17 due to the ambiguous implementation,
    // and its improper error handling when reading file in unexpected code point.
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string line;
    #elif __linux__
    wifstream source_csv(_CSV_SOURCE_PATH);
    source_csv.imbue(locale("C.UTF-8"));
    #endif

    #if defined(_WIN32) || defined(__WIN32__)
    while(getline(source_csv, line)){
        wline = converter.from_bytes(line.c_str());
    #elif __linux__
    while(getline(source_csv, wline)){
    #endif
        record.clear();
        for(auto &wc:wline){
            if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && wc==left_p)  between_parentheses = true;
            if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && wc==right_p)  between_parentheses = false;
            
            if(wc==delim){
                record.emplace_back(cell);
                cell=L"";
                if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3+1 && merge_mode)  break;
                if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && between_parentheses) merge_mode=true;
            }
            else    cell += wc;
        }
        if(merge_mode){
            merge_prev_record(csv, record, {_CSV_COLUMN_INDEX_ADDRESS_3_PHONETIC,_CSV_COLUMN_INDEX_ADDRESS_3});
            merge_mode = false;
        }
        else{
            record.emplace_back(cell); // last element
            csv.emplace_back(record); // create new record
        }
        cell=L"";
    }

    generate_concatened_csv(csv);
    wcout << L"Generated " << int_size(csv) << L" lines of concatened csv." <<endl;
    
    source_csv.close();
    return;
}