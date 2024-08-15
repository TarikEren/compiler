#include <iostream>
#include "headers/lexer.hpp" //Lexer, Token, string, vector, util.hpp

//TODOS:
// TODO: Check the line and col values.
// TODO: Implement syntax checks in the lexer.
// TODO: Implement single quotes.
// TODO: Fix line and column counters.
// TODO: Recognise underscores.
// TODO: Check for circular includes.
// TODO: Performance optimizations. A lot of them. Specifically adding move constructors.
// TODO: Add argc checks and get file name from argv.
// TODO: Create an error message function aside from the logger that takes in col and line as arguments, stringifies them and prints out a message for the user to see.

//Possible changes:
// The util name is kind of misleading for now. Might change it later.

//Errors and issues:
// If there isn't a space between an integer literal and a string literal, the program goes ape shit.
// There aren't any number checks in identifiers.

int main(int argc, char* argv[]) {
    if (argc < 2) {
        util::log(util::ERROR, "No file provided");
        return util::FILE_NOT_PROVIDED;
    }
    //Initiate lexer
    Lexer lexer_obj{};
    //Read file with checking the result of the function
    auto read_file_result = lexer_obj.read_file(argv[1]);
    //Act accordingly.
    if (read_file_result == util::FILE_NOT_FOUND) {
        return util::FILE_NOT_FOUND;
    }
    //Grab tokens from the tokenizer.
    std::vector<Token*> tokens = lexer_obj.tokenize();
    for (auto tok: tokens) {
        std::cout << Token::token_to_string(tok) << std::endl;
    }
    //TODO: Change this so that the parser takes in the tokens and deletes them as well.
    Lexer::delete_tokens(tokens);
    return util::SUCCESS;
}
