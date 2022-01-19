#ifndef NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#define NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#include <bits/stdc++.h>
#include <fcntl.h>
#include <gtest/gtest.h>
namespace ngramTesting {
using namespace std;
class Utils {
    protected:
    template <typename T>
    pair<string, wstring> getLogPath(T fixture){
        string env = getExctutionEnviroment();
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        string path = "test/test_results/" + env + "/"
                    + string(test_info->test_suite_name()) + "." + string(test_info->name()) + ".log";
        wstring wpath = strToWstr(path);
        return make_pair(path, wpath);
    }
    // On Windows, test log need to be redirect since using _setmode() in initiallizer
    template <typename T>
    void redirectTestLog(T fixture){
        auto [log_path, log_path_w] = getLogPath(this);
        wcerr << L"Log stream redirected to " << log_path_w << endl;

        // redirect (stderr -> stdout -> file)
        // FIXME: redirection doesn't work on linux
        ofs_linux.open(log_path, ios_base::binary);
        cout.rdbuf(ofs_linux.rdbuf());
        cerr.rdbuf(cout.rdbuf());
        wofs_windows.open(log_path, ios_base::binary);
        wcout.rdbuf(wofs_windows.rdbuf());
        wcerr.rdbuf(wcout.rdbuf());
    }
    template <typename T>
    void handleErrorOutput(T fixture){
        auto [log_path, log_path_w] = getLogPath(this);
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        const testing::TestResult* const test_result = test_info->result();
        if(fixture->HasFailure()){
            wcerr << L"Test failed at: " << log_path_w << endl;
            const int error_counts = test_result->total_part_count();
            wcerr << L" Total errors in the current test: " << error_counts << endl;
            for(int i=0; i<error_counts; i++){
                auto test_part_result = test_result->GetTestPartResult(i);
                wcerr << test_part_result.file_name() << L":" << test_part_result.line_number() << endl;
                wcerr << test_part_result.message() << endl;
            }
        } else { // no errors
            ofs_linux.close();
            wofs_windows.close();
            remove(log_path.c_str());
        }
    }
    string getExctutionEnviroment(){
        #if defined(_WIN32) || defined(__WIN32__)
        return "windows";
        #elif __linux__
        return "linux";
        #else
        return "unknown";
        #endif
    }
    wstring strToWstr(string str){
        wstring wstr = converter.from_bytes(str.c_str());
        return wstr;
    }
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    ofstream ofs_linux;
    wofstream wofs_windows;
};
} // namespace ngramTesting
#endif