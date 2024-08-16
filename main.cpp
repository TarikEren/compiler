#include <iostream>
#include "headers/lexer.hpp" //Lexer, Token, string, vector, util.hpp
#include "headers/ast.hpp"

//TODOS:
// TODO: Implement syntax checks in the lexer.
// TODO: Check for circular includes.
// TODO: Performance optimizations. A lot of them. Specifically adding move constructors.
// TODO: Find a compiler and language name. Also an extension.

int main(int argc, char* argv[]) {
    if (argc < 2) {
        util::log(util::INFO, R"(Usage: COMPILER_NAME "file name" "flags")");
        //TODO: Figure out some flags.
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
    AST ast{};
    ast.set_tokens(tokens);
    ast.delete_tokens();
    return util::SUCCESS;
}
