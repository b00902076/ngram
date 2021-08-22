#include "common.h"
// constrains:
// - english filename for input csv
// - Windows10

int main(){
    #if defined(_WIN32) || defined(__WIN32__)
    _setmode(_fileno(stdout), _O_WTEXT);
    setlocale(LC_CTYPE, "japanese");
    #endif
    vector<vector<wstring>> csv;
    vector<wstring> records;
    unordered_map<wstring, unordered_set<int>> index;
    
    // load source file and perform concatenation
    // TODO: seperate loading & concatenating part
    load_csv(csv);
    // load concatened records for quick output
    load_record(records);
    // build index and store at local
    build_index(csv);
    // load index file from the generated one
    load_index(index);
    // search
    search(index, records);

    return 0;
}