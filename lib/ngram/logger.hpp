#ifndef NGRAM_LIB_NGRAM_LOGGER_H
#define NGRAM_LIB_NGRAM_LOGGER_H
#include <ngram/common.hpp>
#include "writter.hpp"
#include "config.hpp"

class Logger: public Writter {
    public:
        Logger(const string& filename);
        Logger(const string& filename, ios_base::openmode mode);
        Logger& operator<<(const int& input);
        Logger& operator<<(const unsigned long& input);
        Logger& operator<<(const string& input);
        Logger& operator<<(const wstring& input);
        Logger& operator<<(Logger& (*func)(Logger&));
        static Logger& endl(Logger&);
        ~Logger();
    
    private:
        bool console_output_utf8;
};
#endif
