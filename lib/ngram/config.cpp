#include "config.hpp"

/**
 *  true: stop putting runtime messages to stdout, but still put to log file.
 *  false: put runtime messages to both stdout and file.
 */
bool Config::mute_stdout = false;

/**
 *  determine the sorting method on search results
 */
int Config::sort_method = _SORT_METHOD_NULL;

/**
 * set true if is in test mode(gTest runtime)
 */
bool Config::test_mode = false;

/**
 * set true if reading queries from stdin
 */
bool Config::fetch_query_from_stdin = false;

void Config::resetAllConfigs() {
    test_mode = false;
    mute_stdout = false;
    sort_method = _SORT_METHOD_NULL;
    fetch_query_from_stdin = false;
    return;
}
