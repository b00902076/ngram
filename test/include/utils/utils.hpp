#ifndef NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#define NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#include <bits/stdc++.h>
#include <gtest/gtest.h>
namespace ngramTesting {
class Utils {
    protected:
    // On Windows, test log need to be redirect since using _setmode() in initiallizer
    // This method should be call ONLY under the windows environment.
    template <typename T>
    void redirectTestLog(T fixture){
        // redirect
        wcerr << L"Log stream redirected to test/test_result[w].log";
        ofs.open("test/test_result.log", std::ios_base::binary);
        wofs.open("test/test_resultw.log", std::ios_base::binary);
        cout.rdbuf(ofs.rdbuf());
        wcout.rdbuf(wofs.rdbuf());
        cerr.rdbuf(ofs.rdbuf());
        wcerr.rdbuf(wofs.rdbuf());

        // handle ouput
        if(fixture->HasFailure()) wcout << L"HasFailure" << endl;
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        const testing::TestResult* const test_result = test_info->result();
        const int total_part_counts = test_result->total_part_count();
        wcout << test_info->name() << L" total part count: " << total_part_counts << endl;
        for(int i=0; i<total_part_counts; i++){
            auto test_part_result = test_result->GetTestPartResult(i);
            wcout << test_part_result.file_name() << L":" << test_part_result.line_number() << endl;
            wcout << test_part_result.message() << endl;
        }
    }
    std::ofstream ofs;
    std::wofstream wofs;
};
} // namespace ngramTesting
#endif