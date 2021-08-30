#include "common.h"

// load index file from the generated one
void load_index(unordered_map<wstring, unordered_set<int>> &index){
    wifstream index_file(_INDEX_FILENAME);
    index_file.imbue(locale("C.UTF-8"));
    wstring line, key, idx;
    while(getline(index_file, line)){
        wstringstream line_stream(line);
        getline(line_stream, key, L' ');
        while(getline(line_stream, idx, L' ')){
            index[key].emplace(stoi(idx));
        }
    }
    wcout << L"Loaded index from local file with " << index.size() << L" keys." << endl;
    index_file.close();
    return;
}