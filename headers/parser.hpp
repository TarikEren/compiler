#ifndef COMPILER_PARSER_HPP
#define COMPILER_PARSER_HPP

#include <vector>
#include "token.hpp"

class Parser {
private:
    std::vector<Token*> tokens{};
public:
    //Sets the tokens variable.
    void set_tokens(std::vector<Token*>);
    //Parses through the provided tokens.
    void parse();
    //Clears the token vector.
    void clear_tokens();
    //Prints the token vector out.
    void dump_tokens();
};

#endif