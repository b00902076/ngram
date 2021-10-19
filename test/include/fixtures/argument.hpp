#ifndef NGRAM_TEST_INCLUDE_ARGUMENT_HPP
#define NGRAM_TEST_INCLUDE_ARGUMENT_HPP
#include <bits/stdc++.h>
#include <gtest/gtest.h>
class Argument {
    public:
        // Argument(int c): argc(c) {}
        int argc;
        char *argv[2];
};

class ArgumentTest: public testing::Test {
    protected:
        void SetUp() override {
            no_flag_arg.argc = 1;
            no_flag_arg.argv[0] = binary;
            for(auto flag:availible_flags){
                Argument arg;
                arg.argc = 2;
                arg.argv[0] = binary;
                arg.argv[1] = flag;
                single_flag_arg_set.push_back(arg);
            }

        }
        void TearDown() override {
            // Windows platform only
            // redirect stdout to handle output messages after Initializer executing _setmode()
            #if defined(_WIN32) || defined(__WIN32__)
            ofs.open("test_result.log", ios_base::binary);
            wofs.open("test_resultw.log", ios_base::binary);
            cout.rdbuf(ofs.rdbuf());
            wcout.rdbuf(wofs.rdbuf());
            if(this->HasFailure()) wcout << L"HasFailure" << endl;
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            const testing::TestResult* const test_result = test_info->result();
            const int total_part_counts = test_result->total_part_count();
            wcout << test_info->name() << L" total part count: " << total_part_counts << endl;
            for(int i=0; i<total_part_counts; i++){
                auto test_part_result = test_result->GetTestPartResult(i);
                wcout << test_part_result.file_name() << L":" << test_part_result.line_number() << endl;
                wcout << test_part_result.message() << endl;
            }
            #endif
        }

        #if defined(_WIN32) || defined(__WIN32__)
        ofstream ofs;
        wofstream wofs;
        #endif
        Argument no_flag_arg;
        vector<Argument> single_flag_arg_set;

    private:
        char *binary = (char *)"dummy.exe";
        vector<char*> availible_flags = {
            (char *)"-m=s", (char *)"--mode=silent",
            (char *)"-s=i", (char *)"--sort=id",
            (char *)"-s=h", (char *)"--sort=hit"
        };
        
};

#endif