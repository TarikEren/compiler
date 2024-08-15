#include <iostream>
#include "headers/lexer.hpp" //Lexer, Token, string, vector, util.hpp

//TODOS:
// TODO: Implement syntax checks in the lexer.
// TODO: Check for circular includes.
// TODO: Performance optimizations. A lot of them. Specifically adding move constructors.

//Errors and issues:
// There aren't any number checks in identifiers.
// (Try implementing a while loop that iterates through the text until it encounters a semicolon or space and checking if there are any numbers in the buffer.)

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
