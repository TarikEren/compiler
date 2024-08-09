#include "headers/lexer.hpp" //Lexer, Token, string, vector, util.hpp
#include "headers/parser.hpp"

//TODOS:
// Check for circular includes
// Performance optimizations. A lot of them. Specifically adding move constructors.
// Add argc checks and get file name from argv.

//Possible changes:
// The util name is kind of misleading for now. Might change it later.

//Errors and issues:
// If there isn't a space between an integer literal and a string literal, the program goes ape shit.
// There aren't any number checks in identifiers.

int main() {
    //Initiate lexer
    Lexer lexer_obj{};
    //Read file with checking the result of the function
    auto read_file_result = lexer_obj.read_file("test");
    //Act accordingly.
    if (read_file_result == util::FILE_NOT_FOUND) {
        return util::FILE_NOT_FOUND;
    }
    //Grab tokens from the tokenizer.
    std::vector<Token*> tokens = lexer_obj.tokenize();
    //Initiate parser
    Parser parser_obj{};
    //Set parser tokens.
    parser_obj.set_tokens(tokens);
    //Parse tokens.
    parser_obj.parse();
    //Print tokens.
    parser_obj.dump_tokens();
    //Remove tokens as they are heap allocated.
    parser_obj.clear_tokens();
    return util::SUCCESS;
}
