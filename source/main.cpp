#include "common.h"
// constrains:
// - linux
// - source file with utf-8 encoding, LF as new line

int main(int argc, char *argv[]){
    // TODO: add excuting time measure
    unordered_set<string> args;
    for(int i=1; i<argc; i++)   args.emplace(argv[i]);

    // without this line, wcout's locale will be bind to cout
    ios_base::sync_with_stdio(false);
    wcin.imbue(locale("C.UTF-8"));
    wcout.imbue(locale("C.UTF-8"));

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
    search(index, records, args);

    return 0;
}