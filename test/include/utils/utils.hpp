#ifndef NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#define NGRAM_TEST_INCLUDE_UTILS_UTILS_HPP
#include <bits/stdc++.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include "./constants.hpp"
using namespace std;
namespace ngramTesting {
class Utils {
    protected:
    template <typename T>
    string getLogPath(T fixture){
        const string env = getExcutionEnviromentStr();
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        string path = "test/test_results/" + env + "/"
                    + string(test_info->test_suite_name()) + "." + string(test_info->name()) + ".log";
        return path;
    }

    /**
     * Redirect logging messages to file. (stderr -> stdout -> file)
     * On Windows, test log need to be redirected since using _setmode() in Initiallizer.
     * On both Windows or Linux, this method should be excuted after Initializer.
     */
    template <typename T>
    void redirectTestLog(T fixture){
        const string env = getExcutionEnviromentStr();
        auto log_path = getLogPath(this);
        if(env == "unknown"){
            cerr << "Not running on the expected OS." << endl
                << "Which may cause unexpected behavior." << endl;
            return;
        }
        else if(env == "linux"){
            // For GTEST library's output
            cerr << "Log stream redirected to: " << (log_path+".gtest") << endl;
            ofs.open(log_path+".gtest", ios_base::binary);
            cout.rdbuf(ofs.rdbuf());
            cerr.rdbuf(cout.rdbuf());

            // For App's output
            wcerr << "App output stream redirected to: " << (log_path+".app").c_str() << endl;
            wofs.open(log_path+".app", ios_base::binary);
            wcout.rdbuf(wofs.rdbuf());
            wcerr.rdbuf(wcout.rdbuf());
        }
        else if(env == "windows"){
            // For App & GTEST output
            // After _setmode() in Class::Initializer, stdout will be redirected to wcout.
            wcerr << "Log stream redirected to: " << log_path.c_str() << endl;
            wofs.open(log_path, ios_base::binary);
            wcout.rdbuf(wofs.rdbuf());
            wcerr.rdbuf(wcout.rdbuf());
        }
    }
    /** 
     * Handles GTEST's output messages after redirection.
     * This method should run ONLY at expected OS.
     * (ie: linux/windows)
     */ 
    template <typename T>
    void handleErrorOutput(T fixture){
        #if defined(_WIN32) || defined(__WIN32__)
        wostream &err_stream = wcerr;
        #elif __linux__
        ostream &err_stream = cerr;
        #endif
        auto log_path = getLogPath(this);
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        const testing::TestResult* const test_result = test_info->result();
        
        if(fixture->HasFailure()){
            const int error_counts = test_result->total_part_count();
            err_stream << "Total errors in the current test: " << error_counts << endl;
            for(int i=0; i<error_counts; i++){
                auto test_part_result = test_result->GetTestPartResult(i);
                err_stream << test_part_result.file_name() << ":" << test_part_result.line_number() << endl;
                err_stream << test_part_result.message() << endl;
            }
            cerr << "Test has failed. For the details, see: " << log_path.c_str() << endl;
            wofs.close();
            ofs.close();
        } else { // no errors
            wofs.close();
            ofs.close();
            #if defined(_WIN32) || defined(__WIN32__)
            remove(log_path.c_str());
            #elif __linux__
            remove((log_path+".gtest").c_str());
            remove((log_path+".app").c_str());
            #endif
        }
    }
    inline string getExcutionEnviromentStr(){
        #if defined(_WIN32) || defined(__WIN32__)
        return "windows";
        #elif __linux__
        return "linux";
        #else
        return "unknown";
        #endif
    }
    inline wstring strToWstr(string str){
        wstring wstr = converter.from_bytes(str.c_str());
        return wstr;
    }
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    ofstream ofs;
    wofstream wofs;
};
} // namespace ngramTesting
#endif