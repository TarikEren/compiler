#include "../headers/util.hpp"
#include <iostream>

void util::log(util::Loglevel level, const std::string& message) {
    switch (level) {
        case INFO:
            std::cout << util::INFO_SEQUENCE << message << std::endl;
            break;
        case WARNING:
            std::cout << util::WARNING_SEQUENCE << message << std::endl;
            break;
        case ERROR:
            std::cout << util::ERROR_SEQUENCE << message << std::endl;
            break;
    }
}

void util::NodeStack::push(AST_Node* new_node) {
    this->top += 1;
    auto temp = (AST_Node**)realloc(this->array, (this->top + 1) * sizeof(AST_Node*));
    if (temp == nullptr) {
        util::log(util::ERROR, "Failed to reallocate memory for the NodeStack");
        free(temp);
        return;
    }
    this->array = temp;
    this->array[this->top] = new_node;
}

AST_Node *util::NodeStack::pop() {
    if (this->top == -1) {
        util::log(util::ERROR, "NodeStack is empty, cannot pop");
        return nullptr;
    }
    this->top -= 1;
}

AST_Node *util::NodeStack::peek() {
    if (this->top == -1) {
        util::log(util::ERROR, "NodeStack is empty, cannot peek");
        return nullptr;
    }
    return this->array[this->top];
}

bool util::NodeStack::is_empty() const {
    return this->top == -1;
}
