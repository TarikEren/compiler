#include <iostream>
#include "headers/lexer.hpp" //Lexer, Token, string, vector, util.hpp

//TODOS:
// Implement syntax checks in the lexer.
// Check for circular includes.
// Performance optimizations. A lot of them. Specifically adding move constructors.
// Add argc checks and get file name from argv.
// Create an error message function aside from the logger that takes in col and line as arguments, stringifies them and prints out a message for the user to see.

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
    for (auto tok: tokens) {
        std::cout << Token::token_to_string(tok) << std::endl;
    }
    lexer_obj.delete_tokens(tokens);
    return util::SUCCESS;
}
