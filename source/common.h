#include <bits/stdc++.h>
#include <fcntl.h>
#if defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif

#define _N_GRAM_LENGTH 2
#define _CSV_COLUMN_INDEX_ADDRESS_1_PHONETIC 3
#define _CSV_COLUMN_INDEX_ADDRESS_2_PHONETIC 4
#define _CSV_COLUMN_INDEX_ADDRESS_3_PHONETIC 5
#define _CSV_COLUMN_INDEX_ADDRESS_1 6
#define _CSV_COLUMN_INDEX_ADDRESS_2 7
#define _CSV_COLUMN_INDEX_ADDRESS_3 8
#define _CSV_SOURCE_FILENAME "KEN_ALL.CSV"
#define _CSV_CONCATENED_FILENAME "KEN_ALL_CONCATENED.CSV"
#define _INDEX_FILENAME "index_file"
#define _SEARCH_RESULT_FILENAME "search_result"
#define _GUIDE_MESSAGE L"検索キーワード（終了する場合はEXITを入力）："
#define _MAX_BUFFER_LENGTH 1000

// TODO: set makefile
using namespace std;
bool avalible_key(wstring &key, unordered_set<wchar_t> &skip_wc);
void load_csv(vector<vector<wstring>> &csv);
void load_record(vector<wstring> &records);
void build_index(vector<vector<wstring>> &csv);
void load_index(unordered_map<wstring, unordered_set<int>> &index);
void search(unordered_map<wstring, unordered_set<int>> &index, vector<wstring> &records, unordered_set<string> &args);
