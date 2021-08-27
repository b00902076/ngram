#include "common.h"

void load_record(vector<wstring> &records){
    wifstream concatened_csv(_CSV_CONCATENED_FILENAME);
    concatened_csv.imbue(locale("C.UTF-8"));
    wstring line;
    while(getline(concatened_csv, line))
        records.emplace_back(line);
    wcout << L"Loaded " << records.size() << " records." <<endl;
    concatened_csv.close();
    return;
}