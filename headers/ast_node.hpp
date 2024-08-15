#ifndef COMPILER_AST_NODE_HPP
#define COMPILER_AST_NODE_HPP

typedef enum AST_NodeType {
    STMT_ASSIGNMENT,
    IDENT,
    EXPR,
    V_INT
}AST_NodeType;

class AST_Node {
private:
    AST_NodeType type{};
    AST_Node *left{}, *right{};
public:
    AST_Node* get_left() {
        return this->left;
    }
    AST_Node* get_right() {
        return this->right;
    }
    void set_left(AST_Node* new_left) {
        this->left = new_left;
    }
    void set_right(AST_Node* new_right) {
        this->right = new_right;
    }
    void set_type(AST_NodeType new_type) {
        this->type = new_type;
    }
};

class AssignmentNode : public AST_Node {
private:
public:
    AssignmentNode() {
        set_type(STMT_ASSIGNMENT);
    }
};

class IdentifierNode : public AST_Node {
private:
public:
    IdentifierNode() {
        this->set_type(IDENT);
    }
};

class ExpressionNode : public AST_Node {
private:
public:
    ExpressionNode() {
        this->set_type(EXPR);
    }

};

class IntegerValueNode : public AST_Node {
private:
    int value{};
public:
    explicit IntegerValueNode(int value) {
        this->set_type(V_INT);
        this->value = value;
    }
};


#endif
