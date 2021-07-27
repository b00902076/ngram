#include "common.h"

void generate_concatened_csv(vector<vector<wstring>> &csv){
    wofstream concatened_csv(_CSV_CONCATENED_FILENAME);
    for(auto &row:csv){
        for(int i=0; i<row.size(); i++){
            concatened_csv << row[i];
            if(i!=row.size()-1) concatened_csv << L",";
        }
        concatened_csv << endl;
    }
    concatened_csv.close();
    return;
}

void merge_prev_record(vector<vector<wstring>> &csv, vector<wstring> &record, vector<int> target_columns){
    wstring prev, current;
    for(auto &col:target_columns){
        prev = csv.back()[col];
        current = record[col];
        csv.back()[col] = prev.substr(0, prev.size()-1) + current.substr(1, current.size()-1);
    }
    return;
}

void load_csv(vector<vector<wstring>> &csv){
    wifstream source_csv;
    bool between_parentheses=false, merge_mode=false;
    int line_count=0;
    wchar_t delim=L',', left_p=L'（', right_p=L'）';
    wstring line, cell=L"";

    source_csv.open(_CSV_SOURCE_FILENAME);
    while(getline(source_csv, line)){
        vector<wstring> record;
        for(auto &wc:line){
            // 
            if(record.size()==8 && wc==left_p)  between_parentheses = true;
            if(record.size()==8 && wc==right_p)  between_parentheses = false;
            
            if(wc==delim){
                record.emplace_back(cell);
                cell=L"";
                if(record.size()==9 && merge_mode)  break;
                if(record.size()==8 && between_parentheses) merge_mode=true;
            }
            else    cell += wc;
        }
        if(merge_mode){
            merge_prev_record(csv, record, {5,8});
            merge_mode = false;
        }
        else{
            record.emplace_back(cell); // last element
            csv.emplace_back(record); // create new record
        }
        cell=L"";
        line_count++;
    }

    generate_concatened_csv(csv);
    wcout << L"Generated " << csv.size() << L" lines of concatened csv." <<endl;
    
    source_csv.close();
    return;
}