#include "headers/search.hpp"
#include "components/utils/utils.hpp"
#include "components/logger/logger.hpp"
#include "config/config.hpp"

void output_search_result(vector<wstring> &records, vector<pair<int,int>> &results){
    Writter FileWritter(_SEARCH_RESULT_PATH);
    for(auto &result:results){
        int record_id = result.first;
        FileWritter << records[record_id] << Writter::endl;
    }
    return;
}

void search(unordered_map<wstring, unordered_set<int>> &index, vector<wstring> &records){
    Config config;
    Logger logger(_LOG_PATH);
    unordered_map<int,int> results_raw; // [{record_id, hit_count}, ...]
    vector<pair<int,int>> results; // [{record_id, hit_count}, ...]
    unordered_set<wchar_t> skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
    wstring line;

    logger << _GUIDE_MESSAGE;
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
        logger << line << Logger::endl;
        if(line == L"EXIT") break;
        if(int_size(line)==0){
            logger << _GUIDE_MESSAGE;
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

        if(config.sort_method > _SORT_METHOD_NULL){
            auto compare = [&config](pair<int,int> &pa, pair<int,int> &pb){
                auto &[record_id_a, hit_count_a] = pa;
                auto &[record_id_b, hit_count_b] = pb;
                if(config.sort_method & _SORT_METHOD_BY_HITS){
                    if(hit_count_a == hit_count_b)  return record_id_a < record_id_b;
                    return hit_count_a > hit_count_b;
                } else {
                    return record_id_a < record_id_b;
                }
            };
            sort(results.begin(), results.end(), compare);
        }

        output_search_result(records, results);

        logger << L"計 " << int_size(results);
        logger << L" 件の検索結果を「" << _SEARCH_RESULT_PATH << L"」にて確認できます。" << Logger::endl;
        logger << _GUIDE_MESSAGE;
    }

    #if defined(_WIN32) || defined(__WIN32__)
    DWORD error_id = GetLastError();
    if(error_id){
        // TODO: winapi throws error when input L"EXIT" to quit program
        LPSTR messageBuffer = nullptr;
        DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        DWORD languageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
        Logger error(_ERROR_LOG_PATH, ios_base::binary);

        size_t size = FormatMessageA(flags, NULL, error_id, languageId, (LPSTR)&messageBuffer, 0, NULL);
        string message(messageBuffer, size);
        error << L"error_code: " << error_id << Logger::endl;
        error << message << Logger::endl;
        LocalFree(messageBuffer);
    }
    #endif
    
    return;
}