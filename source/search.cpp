#include "headers/search.hpp"
#include "components/utils/utils.hpp"

auto sort_by_hits_comp = [](pair<int,int> &pa, pair<int,int> &pb){
    auto &[record_id_a, hit_count_a] = pa;
    auto &[record_id_b, hit_count_b] = pb;
    if(hit_count_a == hit_count_b)  return record_id_a < record_id_b;
    return hit_count_a > hit_count_b;
};

auto sort_by_record_id_comp = [](pair<int,int> &pa, pair<int,int> &pb){
    auto &[record_id_a, hit_count_a] = pa;
    auto &[record_id_b, hit_count_b] = pb;
    return record_id_a < record_id_b;
};

void output_search_result(vector<wstring> &records, vector<pair<int,int>> &results){
    #if defined(_WIN32) || defined(__WIN32__)
    ofstream search_result(_SEARCH_RESULT_PATH, ios_base::binary);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    for(auto &[record_id, hit_count]: results)
        search_result << converter.to_bytes(records[record_id]) << endl;

    #elif __linux__
    wofstream search_result(_SEARCH_RESULT_PATH, ios_base::binary);
    search_result.imbue(locale("C.UTF-8"));
    for(auto &[record_id, hit_count]: results)
        search_result << records[record_id] << endl;
    #endif

    search_result.close();
    return;
}

void search(unordered_map<wstring, unordered_set<int>> &index, vector<wstring> &records, unordered_set<string> &args){
    // TODO: use class to handle configs
    bool silent_mode = (args.count("-m=s")>0 || args.count("--mode=silent")>0);
    bool sort_by_hits = (args.count("-s=h")>0 || args.count("--sort=hit")>0);
    bool sort_by_id = (args.count("-s=i")>0 || args.count("--sort=id")>0);
    wstring line;
    string b_input;
    unordered_map<int,int> results_raw; // [{record_id, hit_count}, ...]
    vector<pair<int,int>> results; // [{record_id, hit_count}, ...]
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};

    if(silent_mode)    wcout.setstate(ios_base::failbit);
    wcout << _GUIDE_MESSAGE;
    #if defined(_WIN32) || defined(__WIN32__)
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT);
    wchar_t buffer[_MAX_BUFFER_LENGTH]={0};
    DWORD inputsRead;
    CONSOLE_READCONSOLE_CONTROL conReadControl;
    FlushConsoleInputBuffer(hInput);
    while(ReadConsoleW(hInput, buffer, sizeof(buffer), &inputsRead, &conReadControl)){
        line = wstring(buffer, inputsRead-2); // -2 for stripping L'\r' and L'\n'

    #elif __linux__
    while(getline(wcin, line)){
    #endif
        results_raw.clear();
        results.clear();
        if(line == L"EXIT") break;
        if(int_size(line)==0){
            wcout << _GUIDE_MESSAGE;
            continue;
        }

        for(int i=0; i<int_size(line)-(_N_GRAM_LENGTH-1); i++){
            wstring key = line.substr(i,_N_GRAM_LENGTH);
            if(index.count(key)>0 && Utils::availableKey(key, skip_wc)){
                for(auto value:index[key])  results_raw[value]++;
            }
        }

        for(auto &[line_num, hit_count]:results_raw)
            results.emplace_back(line_num, hit_count);

        if(sort_by_hits||sort_by_id){
            auto sort_method = sort_by_hits? sort_by_hits_comp : sort_by_record_id_comp;
            sort(results.begin(), results.end(), sort_method);
        }

        output_search_result(records, results);

        if(silent_mode)     wcout.clear();
        wcout << L"計 " << int_size(results);
        wcout << L" 件の検索結果を「.\\search_result」にて確認できます。" << endl;
        if(silent_mode)     wcout.setstate(ios_base::failbit);
        
        wcout << _GUIDE_MESSAGE;
    }
    
    wcout.clear(); // reset failbit in silent-mode
    return;
}