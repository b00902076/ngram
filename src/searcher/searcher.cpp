#include "searcher.hpp"
#include "../shared/query_fetcher.hpp"
#include "methods/load_record.cc"
#include "methods/search.cc"

Searcher::Searcher(Indexer& indexer):
    indexer(indexer),
    logger(Config::test_mode? _LOG_PATH_TEST:_LOG_PATH),
    error_logger(Config::test_mode? _ERROR_LOG_PATH_TEST:_ERROR_LOG_PATH),
    query_fetcher(Config::test_mode? _SEARCH_QUERY_PATH_TEST:_SEARCH_QUERY_PATH)
{
    skip_wc = {L'、', L'（', L'）', L'～', L' ', L'　'};
    guide_message=L"（EXITを入力して終了）検索キーワード：";
}
