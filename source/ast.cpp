#include <utility>

#include "../headers/ast.hpp"

void AST::delete_tokens() {
    for (auto tok: this->tokens) {
        delete tok;
    }
}

void AST::free_tree() {

}

void AST::parse_tokens() {
    for (auto tok: this->tokens) {
        //Parse through the provided tokens and act upon them.
    }
}

void AST::set_tokens(std::vector<Token *> new_tokens) {
    this->tokens = std::move(new_tokens);
}
