#include "logger.hpp"
#include "../../config/config.hpp"

ios_base::openmode default_mode = ios_base::binary | ios_base::app;
Logger::Logger(const string& filename)
: Writter(filename, default_mode){
    // TODO: timestamp
    if(Config::mute_stdout) wcout.setstate(ios_base::failbit);
}

Logger::Logger(const string& filename, ios_base::openmode mode)
: Writter(filename, mode){
    if(Config::mute_stdout) wcout.setstate(ios_base::failbit);
}

Logger& Logger::operator<<(const int& input){
    Writter::operator<<(input);
    wcout << input;
    return *this;
}

Logger& Logger::operator<<(const unsigned long& input){
    Writter::operator<<(input);
    wcout << input;
    return *this;
}

Logger& Logger::operator<<(const string& input){
    Writter::operator<<(input);
    wcout << converter.from_bytes(input.c_str());
    return *this;
}

Logger& Logger::operator<<(const wstring& input){
    Writter::operator<<(input);
    wcout << input;
    return *this;
}

/**
 *  @brief Interface for manipulators such as @c Logger::endl .
 *  Acutal usage would be like "(Logger) << Logger::endl".
 */
Logger& Logger::operator<<(Logger& (*func)(Logger&)){
    return func(*this);
}

Logger& Logger::endl(Logger& _self){
    _self.stream << std::endl;
    wcout << std::endl;
    return _self;
}

Logger::~Logger(){
    if(Config::mute_stdout && (wcout.rdstate() & ios_base::failbit))
        wcout.clear(wcout.rdstate() & ~ios_base::failbit); // reset failbit
}
