#ifndef COMPILER_LEXER_HPP
#define COMPILER_LEXER_HPP

#include "util.hpp"
#include "token.hpp"
#include <vector>

class Lexer {
private:
    std::string text{};
    size_t text_len{};
    char current{};
    size_t index{};
public:
    //Read file and initialise the text variable.
    util::Exitcode read_file(const std::string&);

    //Move forward one character.
    void advance();

    //Steps back one character.
    void step_back();

    //Show tne next character.
    char peek();

    //Iterate through the text variable and tokenize.
    std::vector<Token*> tokenize();

    //Checks if the provided string is a keyword or not.
    static bool is_keyword(const std::string&);

    //Deletes the tokens
    static void delete_tokens(const std::vector<Token*>&);
};

#endif