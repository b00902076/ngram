#include "indexer.hpp"
Indexer::Indexer(){
    // load source file and perform concatenation
    // TODO: seperate loading & concatenating part
    load_csv();
    // load concatened records for quick output
    load_record();
    // build index and store at local
    build_index();
    // load index file from the generated one
    load_index();
}

// store index content as file
void Indexer::generate_index_file(){
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

void Indexer::build_index(){
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

    generate_index_file();
    return;
}

void Indexer::load_index(){
    wstring wline;
    Reader FileReader(_INDEX_PATH);
    Logger logger(_LOG_PATH);
    
    while(FileReader.readLine(wline)){
        wstringstream line_stream(wline);
        wstring key, idx;
        getline(line_stream, key, L' ');
        while(getline(line_stream, idx, L' ')){
            index[key].emplace(stoi(idx));
        }
    }
    logger << L"Loaded index from local file with " << int_size(index) << L" keys." << Logger::endl;
    return;
}

void Indexer::generate_concatened_csv(){
    Writter FileWritter(_CSV_CONCATENED_PATH);
    for(auto &row:csv){
        for(int i=0; i<int_size(row); i++){
            FileWritter << row[i] << (i==int_size(row)-1? L"\n":L",");
        }
    }
    return;
}

void Indexer::merge_prev_record(vector<wstring> &record, vector<int> target_columns){
    wstring prev, current;
    for(auto &col:target_columns){
        prev = csv.back()[col];
        current = record[col];
        csv.back()[col] = prev.substr(0, int_size(prev)-1) + current.substr(1, int_size(current)-1);
    }
    return;
}

void Indexer::load_csv(){
    bool between_parentheses=false, merge_mode=false;
    wchar_t delim=L',', left_p=L'（', right_p=L'）';
    wstring wline, cell=L"";
    vector<wstring> record;
    Reader FileReader(_CSV_SOURCE_PATH);
    Logger logger(_LOG_PATH);

    while(FileReader.readLine(wline)){
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
            vector<int> target_columns = {_CSV_COLUMN_INDEX_ADDRESS_3_PHONETIC,_CSV_COLUMN_INDEX_ADDRESS_3};
            merge_prev_record(record, target_columns);
            merge_mode = false;
        }
        else{
            record.emplace_back(cell); // last element
            csv.emplace_back(record); // create new record
        }
        cell=L"";
    }

    generate_concatened_csv();
    logger << L"Generated " << int_size(csv) << L" lines of concatened csv." << Logger::endl;
    
    return;
}

void Indexer::load_record(){
    wstring wline;
    Reader FileReader(_CSV_CONCATENED_PATH);
    Logger logger(_LOG_PATH);
    while(FileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    logger << L"Loaded " << int_size(records) << L" records." << Logger::endl;
    return;
}
