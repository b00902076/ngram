#include "common.h"

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

void search(unordered_map<wstring, unordered_set<int>> &index, vector<wstring> &records, unordered_set<string> &args){
    // TODO: use class to handle configs
    bool silent_mode = (args.count("-m=s")>0 || args.count("--mode=silent")>0);
    bool sort_by_hits = (args.count("-s=h")>0 || args.count("--sort=hit")>0);
    bool sort_by_id = (args.count("-s=i")>0 || args.count("--sort=id")>0);
    bool print_result = (args.count("-p")>0 || args.count("--print-result")>0);
    wstring line;
    unordered_map<int,int> results_raw; // [{record_id, hit_count}, ...]
    vector<pair<int,int>> results_sort; // [{record_id, hit_count}, ...]
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};

    if(silent_mode)    wcout.setstate(ios_base::failbit);
    wcout << L"検索キーワードを入力（終了したい場合はexitを入力）：";
    while(getline(wcin, line)){
        results_raw.clear();
        results_sort.clear();
        if(line == L"exit") break;

        for(int i=0; i<line.size()-(N-1); i++){
            wstring key = line.substr(i,N);
            if(index.count(key)>0 && avalible_key(key, skip_wc)){
                for(auto value:index[key])  results_raw[value]++;
            }
        }

        for(auto &[line_num, hit_count]:results_raw)
            results_sort.emplace_back(line_num, hit_count);

        if(sort_by_hits||sort_by_id){
            auto sort_method = sort_by_hits? sort_by_hits_comp : sort_by_record_id_comp;
            sort(results_sort.begin(), results_sort.end(), sort_method);
        }

        if(print_result){
            for(auto &[record_id, hit_count]: results_sort)
                wcout << records[record_id] << endl;
            wcout << L"検索結果計 " << results_sort.size() << L"件" << endl;
        }
        else{
            wofstream search_result(_SEARCH_RESULT_FILENAME);
            search_result.imbue(locale("C.UTF-8"));
            for(auto &[record_id, hit_count]: results_sort)
                search_result << records[record_id] << endl;
            search_result.close();
            if(silent_mode){
                wcout.clear();
                wcout << L"計 " << results_sort.size();
                wcout << L" 件の検索結果を「.\\search_result」にて確認できます。" << endl;
                wcout.setstate(ios_base::failbit);
            }
        }
        wcout << L"検索キーワードを入力（終了したい場合はexitを入力）：";
    }
    
    wcout.clear(); // reset failbit in silent-mode
    return;
}