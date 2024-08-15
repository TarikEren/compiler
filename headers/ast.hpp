#ifndef COMPILER_AST_HPP
#define COMPILER_AST_HPP

#include "ast_node.hpp"
#include <vector>

class AST {
private:
    AST_Node* root;
public:
    AST(AST_Node* root) {
        this->root = root;
    }
    void free_tree() {

    }
    void parse_tree() {

    }
};

#endif
