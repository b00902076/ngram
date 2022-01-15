#include "../../../include/ngram/searcher.hpp"
#include "../../lib/ngram/query_fetcher.hpp"

void Searcher::outputSearchResult(vector<pair<int,int>> &results){
    string file_path = Config::test_mode? _SEARCH_RESULT_PATH_TEST:_SEARCH_RESULT_PATH;
    Writter FileWritter(file_path);
    for(auto &result:results){
        int record_id = result.first;
        FileWritter << records[record_id] << Writter::endl;
    }
    return;
}

#if defined(_WIN32) || defined(__WIN32__)
void Searcher::handleErrorWIN32(){
    DWORD error_id = GetLastError();
    string error_path = Config::test_mode? _ERROR_LOG_PATH_TEST:_ERROR_LOG_PATH;
    if(error_id){
        // TODO: survey: winapi randomly throws error when input L"EXIT" to quit program
        LPSTR messageBuffer = nullptr;
        DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        DWORD languageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
        Logger error(error_path, ios_base::binary);

        size_t size = FormatMessageA(flags, NULL, error_id, languageId, (LPSTR)&messageBuffer, 0, NULL);
        string message(messageBuffer, size);
        error << L"error_code: " << error_id << Logger::endl;
        error << message << Logger::endl;
        LocalFree(messageBuffer);
    }
}
#endif

void Searcher::search(){
    string search_result_path = Config::test_mode? _SEARCH_RESULT_PATH_TEST:_SEARCH_RESULT_PATH;
    unordered_map<int,int> results_raw; // [{record_id, hit_count}, ...]
    vector<pair<int,int>> results; // [{record_id, hit_count}, ...]
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
    wstring wline, guide_message=L"（EXITを入力して終了）検索キーワード：";
    QueryFetcher query_fetcher(_SEARCH_QUERY_PATH);

    logger << guide_message;
    while(query_fetcher.fetchOneQuery(wline)){
        if(!Config::fetch_query_from_stdin)
            wcout << wline << endl; // just for the readability of output
        results_raw.clear();
        results.clear();
        if(wline == L"EXIT") break;
        if(int_size(wline)==0){
            logger << guide_message;
            continue;
        }

        for(int i=0; i<int_size(wline)-(_N_GRAM_LENGTH-1); i++){
            wstring key = wline.substr(i,_N_GRAM_LENGTH);
            // TODO: get rid of indexer here
            if(indexer.index.count(key)>0 && Utils::availableKey(key, skip_wc)){
                for(auto value:indexer.index[key])  results_raw[value]++;
            }
        }

        for(auto &[line_num, hit_count]:results_raw)
            results.emplace_back(line_num, hit_count);

        if(Config::sort_method > _SORT_METHOD_NULL){
            auto compare = [](pair<int,int> &pa, pair<int,int> &pb){
                auto &[record_id_a, hit_count_a] = pa;
                auto &[record_id_b, hit_count_b] = pb;
                if(Config::sort_method & _SORT_METHOD_BY_HITS){
                    // In this mode, the record containing more DISTINCT key goes former
                    if(hit_count_a == hit_count_b)  return record_id_a < record_id_b;
                    return hit_count_a > hit_count_b;
                } else {
                    return record_id_a < record_id_b;
                }
            };
            sort(results.begin(), results.end(), compare);
        }

        outputSearchResult(results);

        logger << L"計 " << int_size(results);
        logger << L" 件の検索結果を「" << search_result_path << L"」にて確認できます。" << Logger::endl;
        logger << guide_message;
    }

    #if defined(_WIN32) || defined(__WIN32__)
    handleErrorWIN32();
    #endif
    
    return;
}
