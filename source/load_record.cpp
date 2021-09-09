#include "headers/load_record.hpp"
#include "components/reader/reader.hpp"

void load_record(vector<wstring> &records){
    wstring wline;
    Reader fileReader(_CSV_CONCATENED_PATH);
    while(fileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    // #if defined(_WIN32) || defined(__WIN32__)
    // ifstream concatened_csv(_CSV_CONCATENED_PATH, ios_base::binary);
    // wstring_convert<codecvt_utf8<wchar_t>> converter;
    // string line;
    // wstring wline;
    // while(getline(concatened_csv, line)){
    //     wline = converter.from_bytes(line.c_str());
    //     records.emplace_back(wline);
    // }
    // #elif __linux__
    // wifstream concatened_csv(_CSV_CONCATENED_PATH, ios_base::binary);
    // concatened_csv.imbue(locale("C.UTF-8"));
    // wstring line;
    // while(getline(concatened_csv, line))
    //     records.emplace_back(line);
    // #endif
    wcout << L"Loaded " << int_size(records) << " records." <<endl;
    // concatened_csv.close();
    return;
}