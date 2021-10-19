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

void Config::resetAllConfigs() {
    mute_stdout = false;
    sort_method = _SORT_METHOD_NULL;
    return;
}
