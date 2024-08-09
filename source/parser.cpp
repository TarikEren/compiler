#include <utility>
#include <iostream>
#include "../headers/parser.hpp"

void Parser::clear_tokens() {
    for (auto token: this->tokens) {
        delete token;
    }
}

void Parser::set_tokens(std::vector<Token *> new_tokens) {
    this->tokens = std::move(new_tokens);
}

void Parser::parse() {

}

void Parser::dump_tokens() {
    std::cout << "Tokens start" << std::endl;
    for (auto tok: this->tokens) {
        std::cout << Token::token_to_string(tok) << std::endl;
    }
    std::cout << "Tokens end" << std::endl;
}
