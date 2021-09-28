#include "headers/load_index.hpp"
#include "components/reader/reader.hpp"
#include "components/logger/logger.hpp"

// load index file from the generated one
void load_index(unordered_map<wstring, unordered_set<int>> &index){
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