#include "../../../include/ngram/searcher.hpp"

void Searcher::outputSearchResult(vector<pair<int,int>> &results){
    for(auto &result:results){
        int record_id = result.first;
        result_writter << records[record_id] << Writter::endl;
    }
    logger << L"計 " << int_size(results);
    logger << L" 件の検索結果を「" << result_writter.getFilename() << L"」にて確認できます。" << Logger::endl;
    logger << guide_message;
    return;
}

// TODO: split this to independent module
// (something like error_handler_win32.cpp)
#if defined(_WIN32) || defined(__WIN32__)
void Searcher::handleErrorWIN32(){
    DWORD error_id = GetLastError();
    if(error_id){
        // TODO: survey: winapi randomly throws error when input L"EXIT" to quit program
        LPSTR messageBuffer = nullptr;
        DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        DWORD languageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

        size_t size = FormatMessageA(flags, NULL, error_id, languageId, (LPSTR)&messageBuffer, 0, NULL);
        string message(messageBuffer, size);
        error_logger << L"error_code: " << error_id << Logger::endl;
        error_logger << message << Logger::endl;
        LocalFree(messageBuffer);
    }
}
#endif

/**
 * Returns count of results.
*/
int Searcher::proccessOneQuery(wstring &query, Indexer &indexer){
    unordered_map<int,int> results_raw; // [{record_id, hit_count}, ...]
    vector<pair<int,int>> results; // [{record_id, hit_count}, ...]
    
    // Echoes input when not listening by stdin, just for the readability of output
    if(!Config::fetch_query_from_stdin) wcout << query << endl;

    // For empty input line, but not EOF
    if(int_size(query)==0){
        logger << guide_message;
        return 0;
    }

    // Normal queries
    for(int i=0; i<int_size(query)-(_N_GRAM_LENGTH-1); i++){
        wstring key = query.substr(i,_N_GRAM_LENGTH);
        // TODO: get rid of indexer here
        // create index loader class
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
    return results.size();
}

void Searcher::search(){
    wstring query;
    logger << guide_message;
    while(query_fetcher.fetchOneQuery(query)){
        if(query == L"EXIT") break;
        proccessOneQuery(query, indexer);
    }

    #if defined(_WIN32) || defined(__WIN32__)
    handleErrorWIN32();
    #endif
    
    return;
}
