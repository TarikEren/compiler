#ifndef COMPILER_UTIL_HPP
#define COMPILER_UTIL_HPP

#include <string>

namespace util {

    //Exit codes
    typedef enum ExitCodes {
        SUCCESS,
        FILE_NOT_FOUND,
    }Exitcode;

    typedef enum LogLevels {
        INFO,
        WARNING,
        ERROR,
    }Loglevel;


    //Colored strings
    constexpr char INFO_SEQUENCE[16] = "\x1b[36mInfo:\x1b[0m ";
    constexpr char WARNING_SEQUENCE[19] = "\x1b[33mWarning:\x1b[0m ";
    constexpr char ERROR_SEQUENCE[17] = "\x1b[31mError:\x1b[0m ";

    //Keywords
    constexpr int KEYWORD_COUNT = 13;
    constexpr const char* keywords[KEYWORD_COUNT] = {"int",
                                                     "char",
                                                     "string",
                                                     "bool",
                                                     "if",
                                                     "else",
                                                     "for",
                                                     "do",
                                                     "while",
                                                     "break",
                                                     "return",
                                                     "true",
                                                     "false"};

    void log(Loglevel, const std::string&);
}

#endif