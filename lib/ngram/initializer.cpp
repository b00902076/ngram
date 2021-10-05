#include "initializer.hpp"

Initializer::Initializer(int argc, char *argv[]){
    // handle args
    unordered_set<string> args;
    for(int i=1; i<argc; i++)   args.emplace(argv[i]);
    Config config;
    config.mute_stdout = (args.count("-m=s")>0 || args.count("--mode=silent")>0);
    config.sort_method |= (args.count("-s=i")>0 || args.count("--sort=id")>0)? _SORT_METHOD_BY_ID:0;
    config.sort_method |= (args.count("-s=h")>0 || args.count("--sort=hit")>0)? _SORT_METHOD_BY_HITS:0;

    // stdio stuff
    #if defined(_WIN32) || defined(__WIN32__)
    _setmode(_fileno(stdout), _O_WTEXT);
    #elif __linux__
    // without this line, wcout's locale will be bind to cout
    ios_base::sync_with_stdio(false);
    wcin.imbue(locale("C.UTF-8"));
    wcout.imbue(locale("C.UTF-8"));
    #endif
}