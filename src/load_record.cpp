#include "headers/load_record.hpp"
#include "components/reader/reader.hpp"

void load_record(vector<wstring> &records){
    wstring wline;
    Reader FileReader(_CSV_CONCATENED_PATH);
    while(FileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    wcout << L"Loaded " << int_size(records) << " records." <<endl;
    return;
}