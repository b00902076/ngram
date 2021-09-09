#include "common.hpp"
#include "constants.hpp"
#include "../components/reader/reader.hpp"

void generate_concatened_csv(vector<vector<wstring>> &csv);
void merge_prev_record(vector<vector<wstring>> &csv, vector<wstring> &record, vector<int> target_columns);
void load_csv(vector<vector<wstring>> &csv);
