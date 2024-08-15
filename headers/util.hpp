#ifndef COMPILER_UTIL_HPP
#define COMPILER_UTIL_HPP

#include <string>
#include "ast_node.hpp"

namespace util {

    //Exit codes
    typedef enum ExitCodes {
        SUCCESS,
        FILE_NOT_FOUND,
        FILE_NOT_PROVIDED
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

    //Keywords. A lot C like I know.
    constexpr int KEYWORD_COUNT = 14;
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
                                                     "function",
                                                     "true",
                                                     "false"};

    void log(Loglevel, const std::string&);

    class NodeStack {
    private:
        AST_Node** array{};
        size_t top{};
    public:
        NodeStack() {
            this->top = -1;
            this->array = (AST_Node**)calloc(this->top + 1, sizeof(AST_Node*));
        }
        void push(AST_Node* new_node);
        AST_Node* pop();
        AST_Node* peek();
        bool is_empty() const;
    };
}

#endif