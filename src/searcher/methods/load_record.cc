#include <ngram/searcher.hpp>

void Searcher::loadRecord(){
    wstring wline;
    Reader FileReader(_CSV_CONCATENED_PATH);
    Logger logger(_LOG_PATH);
    while(FileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    logger << L"Loaded " << int_size(records) << L" records." << Logger::endl;
    return;
}