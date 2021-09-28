#include "headers/load_record.hpp"
#include "components/reader/reader.hpp"
#include "components/logger/logger.hpp"

void load_record(vector<wstring> &records){
    wstring wline;
    Reader FileReader(_CSV_CONCATENED_PATH);
    Logger logger(_LOG_PATH);
    while(FileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    logger << L"Loaded " << int_size(records) << L" records." << Logger::endl;
    return;
}