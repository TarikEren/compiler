#ifndef COMPILER_AST_HPP
#define COMPILER_AST_HPP

#include "ast_node.hpp"
#include "token.hpp"
#include <vector>

class AST {
private:
    AST_Node* root;
    std::vector<Token*> tokens;
public:
    explicit AST() = default;
    //Provides the new_tokens to the ast.
    void set_tokens(std::vector<Token*> new_tokens);
    //Frees the resulting tree
    void free_tree();
    //Parses the provided tokens and generates an abstract syntax tree
    void parse_tokens();
    //Deletes the provided tokens as they are heap allocated
    void delete_tokens();
};

#endif
