#include "../headers/token.hpp"

std::string Token::token_to_string(Token* token) {
    std::string new_type{};
    switch (token->type) {
        case VT_INT:
            new_type = "VT_INT";
            break;
        case KT_INT:
            new_type = "KT_INT";
            break;
        case KT_CHAR:
            new_type = "KT_CHAR";
            break;
        case KT_STRING:
            new_type = "KT_STRING";
            break;
        case KT_BOOL:
            new_type = "KT_BOOL";
            break;
        case KT_RETURN:
            new_type = "KT_RETURN";
            break;
        case KT_FUNCTION:
            new_type = "KT_FUNCTION";
            break;
        case KT_IF:
            new_type = "KT_IF";
            break;
        case KT_ELSE:
            new_type = "KT_ELSE";
            break;
        case KT_FOR:
            new_type = "KT_FOR";
            break;
        case KT_DO:
            new_type = "KT_DO";
            break;
        case KT_WHILE:
            new_type = "KT_WHILE";
            break;
        case KT_BREAK:
            new_type = "KT_BREAK";
            break;
        case VT_CHAR:
            new_type = "VT_CHAR";
            break;
        case VT_BOOL:
            new_type = "VT_BOOL";
            break;
        case VT_STRING:
            new_type = "VT_STRING";
            break;
        case VT_IDENT:
            new_type = "VT_IDENT";
            break;
        case T_BANG:
            new_type = "T_BANG";
            break;
        case T_EQUAL:
            new_type = "T_EQUAL";
            break;
        case T_L_ANGLE:
            new_type = "T_L_ANGLE";
            break;
        case T_R_ANGLE:
            new_type = "T_R_ANGLE";
            break;
        case T_PLUS:
            new_type = "T_PLUS";
            break;
        case T_MINUS:
            new_type = "T_MINUS";
            break;
        case T_SLASH:
            new_type = "T_SLASH";
            break;
        case T_STAR:
            new_type = "T_STAR";
            break;
        case T_COLON:
            new_type = "T_COLON";
            break;
        case T_MODULO:
            new_type = "T_MODULO";
            break;
        case T_AMPER:
            new_type = "T_AMPER";
            break;
        case T_L_PAR:
            new_type = "T_L_PAR";
            break;
        case T_R_PAR:
            new_type = "T_R_PAR";
            break;
        case T_L_BRACE:
            new_type = "T_L_BRACE";
            break;
        case T_R_BRACE:
            new_type = "T_R_BRACE";
            break;
        case T_L_BRACKET:
            new_type = "T_L_BRACKET";
            break;
        case T_R_BRACKET:
            new_type = "T_R_BRACKET";
            break;
        case T_SEMI:
            new_type = "T_SEMI";
            break;
        case T_PIPE:
            new_type = "T_PIPE";
            break;
        case T_QUOT:
            new_type = "T_QUOT";
            break;
        case T_HASH:
            new_type = "T_HASH";
            break;
        case T_BACKSLASH:
            new_type = "T_BACKSLASH";
            break;
        case T_EOF:
            new_type = "T_EOF";
            break;
        case T_IS:
            new_type = "T_IS";
            break;
        case T_IS_NOT:
            new_type = "T_IS_NOT";
            break;
        case T_LESS_EQ:
            new_type = "T_LESS_EQ";
            break;
        case T_GREATER_EQ:
            new_type = "T_GREATER_EQ";
            break;
        case T_INCR:
            new_type = "T_INCR";
            break;
        case T_DECR:
            new_type = "T_DECR";
            break;
        case T_AND:
            new_type = "T_AND";
            break;
        case T_OR:
            new_type = "T_OR";
            break;
        case T_COMMENT:
            new_type = "T_COMMENT";
            break;
        default:
            new_type = "UNKNOWN";
            break;
    }
    return "Type: " + new_type + "\t\tValue: " + token->value;
}

void Token::set_token(TokenType new_type, const std::string &new_value) {
    this->value = new_value;
    this->type = new_type;
}

void Token::set_token(TokenType new_type, char new_value) {
    this->value = new_value;
    this->type = new_type;
}

void Token::set_token_type(TokenType new_type) {
    this->type = new_type;
}

void Token::set_token_value(const std::string &new_value) {
    this->value = new_value;
}

TokenType Token::get_token_type() {
    return this->type;
}
