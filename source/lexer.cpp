#include <fstream>
#include <sstream>
#include "../headers/lexer.hpp"

bool Lexer::is_whitespace(char ch) {
    if (ch == '\t' || ch == ' ' || ch == '\r' || ch == '\v' || ch == '\f' || ch == 10) {
        return true;
    }
    return false;
}

//CLion doesn't like the for based range loop, it wants the std::any_of for some reason.
bool Lexer::is_keyword(const std::string& word) {
    for (const auto& keyword: util::keywords) {
        if (word == keyword) return true;
    }
    return false;
}

util::Exitcode Lexer::read_file(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        util::log(util::ERROR, "Unable to open file " + file_name);
        this->text = "";
        return util::FILE_NOT_FOUND;
    }
    std::stringstream stream_buffer;
    stream_buffer << file.rdbuf();
    this->text = stream_buffer.str();
    this->text_len = this->text.size();
    return util::SUCCESS;
}

void Lexer::advance() {
    if (this->index >= this->text_len) {
        return;
    }
    this->index += 1;
    this->current = this->text[this->index];
}

char Lexer::peek() {
    if (this->index + 1 < this->text_len) {
        return this->text[this->index + 1];
    }
    else return '\0';
}

std::vector<Token*> Lexer::tokenize() {
    std::vector<Token*> tokens{};
    size_t col = 1, line = 1;
    this->index = 0;
    this->current = this->text[this->index];
    std::string buffer{};
    while (this->current != '\0') {
        if (Lexer::is_whitespace(this->current)) {
            this->advance();
        }
        if (this->current == '\n') {
            line += 1;
            col = 1;
        }
        switch (this->current) {
            case '!':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_IS_NOT, "!=");
                    this->advance();
                }
                else {
                    token->set_token(T_BANG, '!');
                }
                tokens.push_back(token);
            }
                break;
            case '=':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_IS, "==");
                    this->advance();
                }
                else {
                    token->set_token(T_EQUAL, '=');
                }
                tokens.push_back(token);
            }
                break;
            case '"':
            {
                if (isalnum(this->peek())) {
                    bool found_end_quote = false;
                    size_t str_col = col, str_line = line;
                    //TODO: Check for string literal.
                    while (this->peek() != '"' && current != '\0') {
                        this->advance();
                        if (this->current == '\n') {
                            line += 1;
                            col = 1;
                        } else {
                            col += 1;
                        }
                        buffer.push_back(current);
                        if (this->peek() == '"') {
                            found_end_quote = true;
                            this->advance();
                            break;
                        }
                    }
                    if (!found_end_quote) {
                        std::string stringified_str_line = std::to_string(str_line), stringified_str_col = std::to_string(str_col);
                        std::string message = "Unterminated string starts at line: " + stringified_str_line;
                        message += " col: " + stringified_str_col;
                        util::log(util::ERROR, message);
                    } else {
                        auto str_token = new Token;
                        str_token->set_token(VT_STRING, buffer);
                        tokens.push_back(str_token);
                        buffer.clear();
                    }
                }
                else {
                    auto token = new Token;
                    token->set_token(T_QUOT, '"');
                    tokens.push_back(token);
                }
            }
                break;
            case '<':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_LESS_EQ, "<=");
                    this->advance();
                }
                else {
                    token->set_token(T_L_ANGLE, '<');
                }
                tokens.push_back(token);
            }
                break;
            case '>':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_GREATER_EQ, ">=");
                    this->advance();
                }
                else {
                    token->set_token(T_R_ANGLE, '>');
                }
                tokens.push_back(token);
            }
                break;
            case '&':
            {
                auto token = new Token;
                if (this->peek() == '&') {
                    token->set_token(T_AND, "&&");
                    this->advance();
                }
                else {
                    token->set_token(T_AMPER, '&');
                }
                tokens.push_back(token);
            }
                break;
            case '|':
            {
                auto token = new Token;
                if (this->peek() == '|') {
                    token->set_token(T_OR, "||");
                    this->advance();
                }
                else {
                    token->set_token(T_PIPE, '|');
                }
                tokens.push_back(token);
            }
                break;
            case '/':
            {
                auto token = new Token;
                if (this->peek() == '/') {
                    token->set_token(T_COMMENT, "//");
                    this->advance();
                }
                else {
                    token->set_token(T_SLASH, '/');
                }
                tokens.push_back(token);
            }
                break;
            case '(':
            {
                auto* token = new Token(T_L_PAR, '(');
                tokens.push_back(token);
            }
                break;
            case ')':
            {
                auto token = new Token(T_R_PAR, ')');
                tokens.push_back(token);
            }
                break;
            case '{':
            {
                auto token = new Token(T_L_BRACE, '{');
                tokens.push_back(token);
            }
                break;
            case '}':
            {
                auto token = new Token(T_R_BRACE, '}');
                tokens.push_back(token);
            }
                break;
            case '[':
            {
                auto token = new Token(T_L_BRACKET, '[');
                tokens.push_back(token);
            }
                break;
            case ']':
            {
                auto token = new Token(T_R_BRACKET, ']');
                tokens.push_back(token);
            }
                break;
            case '+':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_INCR, "+=");
                    this->advance();
                }
                else {
                    token->set_token(T_PLUS, '+');
                }
                tokens.push_back(token);
            }
                break;
            case '-':
            {
                auto token = new Token;
                if (this->peek() == '=') {
                    token->set_token(T_DECR, "-=");
                    this->advance();
                }
                else {
                    token->set_token(T_MINUS, '-');
                }
                tokens.push_back(token);
            }
                break;
            case '*':
            {
                auto token = new Token(T_STAR, '*');
                tokens.push_back(token);
            }
                break;
            case ':':
            {
                auto token = new Token(T_COLON, ':');
                tokens.push_back(token);
            }
                break;
            case ';':
            {
                auto token = new Token(T_SEMI, ';');
                tokens.push_back(token);
            }
                break;
            case '%':
            {
                auto token = new Token(T_MODULO, '%');
                tokens.push_back(token);
            }
                break;
            case '#':
            {
                auto token = new Token(T_HASH, '#');
                tokens.push_back(token);
            }
                break;
            default:
                if (isalpha(this->current)){
                    while (isalpha(this->current)) {
                        buffer.push_back(this->current);
                        this->advance();
                        col += 1;
                    }
                    auto token = new Token;
                    if (Lexer::is_keyword(buffer)) {
                        if (buffer == "bool") {
                            token->set_token(KT_BOOL, "bool");
                        }
                        else if (buffer == "int") {
                            token->set_token(KT_INT, "int");
                        }
                        else if (buffer == "char") {
                            token->set_token(KT_CHAR, "char");
                        }
                        else if (buffer == "string") {
                            token->set_token(KT_STRING, "string");
                        }
                        else if (buffer == "for") {
                            token->set_token(KT_FOR, "for");
                        }
                        else if (buffer == "do") {
                            token->set_token(KT_DO, "do");
                        }
                        else if (buffer == "while") {
                            token->set_token(KT_WHILE, "while");
                        }
                        else if (buffer == "break") {
                            token->set_token(KT_BREAK, "break");
                        }
                        else if (buffer == "if") {
                            token->set_token(KT_IF, "if");
                        }
                        else if (buffer == "else") {
                            token->set_token(KT_ELSE, "else");
                        }
                        else if (buffer == "return") {
                            token->set_token(KT_RETURN, "return");
                        }
                        else if (buffer == "function") {
                            token->set_token(KT_FUNCTION, "function");
                        }
                        else if (buffer == "true" || buffer == "false") {
                            token->set_token_type(VT_BOOL);
                            if (buffer == "true") token->set_token_value("true");
                            else token->set_token_value("false");
                        }
                    }
                    else {
                        token->set_token(VT_IDENT, buffer);
                    }
                    tokens.push_back(token);
                    buffer.clear();
                }
                else if (isdigit(this->current)) {
                    while (isdigit(this->current)) {
                        buffer.push_back(this->current);
                        this->advance();
                    }
                    auto token = new Token(VT_INT, buffer);
                    tokens.push_back(token);
                    buffer.clear();
                }
                else {
                    if (!is_whitespace(this->current) && this->current != '\0') {
                        while (!is_whitespace(this->current) && this->current != '\0') {
                            buffer.push_back(this->current);
                            this->advance();
                        }
                        std::string line_str = std::to_string(line),
                        col_str = std::to_string(col),
                        message = "Invalid token " + buffer;
                        message += " at line " + line_str;
                        message += " col: " + col_str;
                        util::log(util::ERROR, message);
                        buffer.clear();
                        advance();
                    }
                }
                this->index -=1;
                break;
        }
        this->advance();
        col += 1;
    }
    auto eof_token = new Token(T_EOF, '\0');
    tokens.push_back(eof_token);
    return tokens;
}

void Lexer::delete_tokens(std::vector<Token*> tokens) {
    for (auto tok: tokens) {
        delete tok;
    }
}
