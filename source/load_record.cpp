#include "common.h"

void load_record(vector<wstring> &records){
    wifstream concatened_csv(_CSV_CONCATENED_FILENAME);
    wstring line;
    while(getline(concatened_csv, line))
        records.emplace_back(line);
    wcout << L"Loaded " << records.size() << " records." <<endl;
    return;
}