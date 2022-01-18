#include "../../../include/ngram/indexer.hpp"

void Indexer::loadIndex(){
    wstring wline;
    string file_path = Config::test_mode? _INDEX_PATH_TEST:_INDEX_PATH;
    Reader file_reader(file_path);
    
    while(file_reader.readLine(wline)){
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