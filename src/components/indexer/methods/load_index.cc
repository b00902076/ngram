#include "../indexer.hpp"

void Indexer::loadIndex(){
    wstring wline;
    Reader FileReader(_INDEX_PATH);
    
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