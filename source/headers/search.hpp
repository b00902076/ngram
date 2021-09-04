#include "common.hpp"
#include "constants.hpp"

void output_search_result(vector<wstring> &records, vector<pair<int,int>> &results);
void search(unordered_map<wstring, unordered_set<int>> &index, vector<wstring> &records, unordered_set<string> &args);
