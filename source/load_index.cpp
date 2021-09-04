#include "headers/load_index.hpp"
#include "headers/constants.hpp"

// load index file from the generated one
void load_index(unordered_map<wstring, unordered_set<int>> &index){
    #if defined(_WIN32) || defined(__WIN32__)
    ifstream index_file(_INDEX_PATH, ios_base::binary);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string line;
    while(getline(index_file, line)){
    #elif __linux__
    wifstream index_file(_INDEX_PATH, ios_base::binary);
    index_file.imbue(locale("C.UTF-8"));
    wstring wline;
    while(getline(index_file, wline)){
    #endif
        #if defined(_WIN32) || defined(__WIN32__)
        wstring wline = converter.from_bytes(line);
        #endif
        
        wstringstream line_stream(wline);
        wstring key, idx;
        getline(line_stream, key, L' ');
        while(getline(line_stream, idx, L' ')){
            index[key].emplace(stoi(idx));
        }
    }
    wcout << L"Loaded index from local file with " << index.size() << L" keys." << endl;
    index_file.close();
    return;
}