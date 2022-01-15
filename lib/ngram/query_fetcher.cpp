#include "query_fetcher.hpp"

QueryFetcher::QueryFetcher(string file_path): Reader(file_path){};

bool QueryFetcher::fetchOneQuery(wstring &wbuffer){
    if(Config::fetch_query_from_stdin){
        #if defined(_WIN32) || defined(__WIN32__)
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(hInput, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT);
        wchar_t buffer[_MAX_BUFFER_LENGTH]={0};
        DWORD inputsRead;
        CONSOLE_READCONSOLE_CONTROL conReadControl;
        FlushConsoleInputBuffer(hInput);
        // ReadConsoleW returns non-zero integer value when operation succeed
        WINBOOL res_bool = ReadConsoleW(hInput, buffer, sizeof(buffer), &inputsRead, &conReadControl);
        if(res_bool)    wbuffer = wstring(buffer, inputsRead-2); // -2 for stripping L'\r\n'
        return res_bool;

        #elif __linux__
        getline(wcin, wbuffer);
        return wcin.good();
        #endif
    } else { // get query from file
        readLine(wbuffer);
        return successfullyRead();
    }
}
