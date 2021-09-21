#pragma once
#include "common.hpp"
#include "build_index.hpp"
#include "load_csv.hpp"
#include "load_index.hpp"
#include "load_record.hpp"
#include "search.hpp"

bool avalible_key(wstring &key, unordered_set<wchar_t> &skip_wc);
