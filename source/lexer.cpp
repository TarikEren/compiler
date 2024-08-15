#include <fstream>
#include <sstream>
#include "../headers/lexer.hpp"

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
    this->index = 0;
    this->current = this->text[this->index];
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

void Lexer::delete_tokens(const std::vector<Token*>& tokens) {
    for (auto tok: tokens) {
        delete tok;
    }
}

std::vector<Token *> Lexer::tokenize() {
    std::vector<Token*> tokens;
    size_t line = 1, col = 0;
    std::string buffer{};

    while (this->current != '\0') {
        Token* token;
        switch (this->current) {
            case '=':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_IS, "==", line, col);
                }
                else {
                    token = new Token(T_EQUAL, '=', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '!':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_IS_NOT, "!=", line, col);
                }
                else {
                    token = new Token(T_BANG, '!', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '>':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_GREATER_EQ, ">=", line, col);
                }
                else {
                    token = new Token(T_R_ANGLE, '>', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '<':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_LESS_EQ, "<=", line, col);
                }
                else {
                    token = new Token(T_L_ANGLE, '<', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '+':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_INCR, "+=", line, col);
                }
                else {
                    token = new Token(T_PLUS, '+', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '-':
            {
                col += 1;
                if (this->peek() == '=') {
                    this->advance();
                    col += 1;
                    token = new Token(T_DECR, "-=", line, col);
                }
                else {
                    token = new Token(T_MINUS, '-', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '&':
            {
                col += 1;
                if (this->peek() == '&') {
                    this->advance();
                    col += 1;
                    token = new Token(T_AND, "&&", line, col);
                }
                else {
                    token = new Token(T_AMPER, '&', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '|':
            {
                col += 1;
                if (this->peek() == '|') {
                    this->advance();
                    col += 1;
                    token = new Token(T_OR, "||", line, col);
                }
                else {
                    token = new Token(T_PIPE, '|', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case ';':
            {
                col += 1;
                token = new Token(T_SEMI, ';', line, col);
                tokens.push_back(token);
            }
                break;
            case '(':
            {
                col += 1;
                token = new Token(T_L_PAR, '(', line, col);
                tokens.push_back(token);
            }
                break;
            case ')':
            {
                col += 1;
                token = new Token(T_R_PAR, ')', line, col);
                tokens.push_back(token);
            }
                break;
            case '{':
            {
                col += 1;
                token = new Token(T_L_BRACE, '{', line, col);
                tokens.push_back(token);
            }
                break;
            case '}':
            {
                col += 1;
                token = new Token(T_R_BRACE, '}', line, col);
                tokens.push_back(token);
            }
                break;
            case '[':
            {
                col += 1;
                token = new Token(T_L_BRACKET, '[', line, col);
                tokens.push_back(token);
            }
                break;
            case ']':
            {
                col += 1;
                token = new Token(T_R_BRACKET, ']', line, col);
                tokens.push_back(token);
            }
                break;
            case '*':
            {
                col += 1;
                token = new Token(T_STAR, '*', line, col);
                tokens.push_back(token);
            }
                break;
            case ':':
            {
                col += 1;
                token = new Token(T_COLON, ':', line, col);
                tokens.push_back(token);
            }
                break;
            case '%':
            {
                col += 1;
                token = new Token(T_MODULO, '%', line, col);
                tokens.push_back(token);
            }
                break;
            case '#':
            {
                col += 1;
                token = new Token(T_HASH, '#', line, col);
                tokens.push_back(token);
            }
                break;
            case '/':
            {
                col += 1;
                if (this->peek() == '/') {
                    this->advance();
                    col += 1;
                    token = new Token(T_COMMENT, "//", line, col);
                    while (this->current != '\n' && this->current != '\0') {
                        this->advance();
                    }
                    line += 1;
                    col = 0;
                }
                else {
                    token = new Token(T_SLASH, '/', line, col);
                }
                tokens.push_back(token);
            }
                break;
            case '\'':
            {
                col += 1;
                if (this->peek() == '\'') {
                    this->advance();
                    col += 1;
                    token = new Token(VT_CHAR, "", line, col);
                }
                else if (isalnum(this->peek())){
                    this->advance();
                    col += 1;
                    buffer.push_back(this->current);
                    if (this->peek() == '\'') {
                        this->advance();
                        col += 1;
                        token = new Token(VT_CHAR, buffer, line, col);
                    }
                    else {
                        util::log(util::ERROR, "Unterminated char at line: " + std::to_string(line) + ", col: " + std::to_string(col));
                    }
                    buffer.clear();
                }
                tokens.push_back(token);
            }
                break;
            case '"':
            {
                col += 1;
                //If string is empty
                if (this->peek() == '"') {
                    this->advance();
                    col += 1;
                    token = new Token(VT_STRING, "", line, col);
                }
                //If string is not empty
                else if (isalnum(this->peek())){
                    bool found_end = false;
                    size_t start_pos = col;
                    while (this->current != '\n' || this->current != '\0') {
                        this->advance();
                        col += 1;
                        buffer.push_back(this->current);
                        if (this->peek() == '"') {
                            found_end = true;
                            break;
                        }
                    }
                    if (found_end) {
                        this->advance();
                        col += 1;
                        token = new Token(VT_STRING, buffer, line, col);
                    }
                    else {
                        util::log(util::ERROR, "Unterminated char at line: " + std::to_string(line) + ", col: " + std::to_string(start_pos));
                    }
                }
                //Else
                else {
                    util::log(util::ERROR, "Unterminated char at line: " + std::to_string(line) + ", col: " + std::to_string(col));
                }
                buffer.clear();
                tokens.push_back(token);
            }
                break;
            default:
                if (isalpha(this->current)) {
                    while (isalpha(this->current) || current == '_') {
                        buffer.push_back(this->current);
                        this->advance();
                        col += 1;
                    }
                    if (is_keyword(buffer)) {
                        if (buffer == "int") {
                            token = new Token(KT_INT, buffer, line, col);
                        }
                        else if (buffer == "bool") {
                            token = new Token(KT_BOOL, buffer, line, col);
                        }
                        else if (buffer == "true" || buffer == "false") {
                            token = new Token(VT_BOOL, buffer, line, col);
                        }
                        else if (buffer == "char") {
                            token = new Token(KT_CHAR, "char", line, col);
                        }
                        else if (buffer == "string") {
                            token = new Token(KT_STRING, "string", line, col);
                        }
                        else if (buffer == "for") {
                            token = new Token(KT_FOR, "for", line, col) ;
                        }
                        else if (buffer == "do") {
                            token = new Token(KT_DO, "do", line, col) ;
                        }
                        else if (buffer == "while") {
                            token = new Token(KT_WHILE, "while", line, col) ;
                        }
                        else if (buffer == "break") {
                            token = new Token(KT_BREAK, "break", line, col) ;
                        }
                        else if (buffer == "if") {
                            token = new Token(KT_IF, "if", line, col) ;
                        }
                        else if (buffer == "else") {
                            token = new Token(KT_ELSE, "else", line, col) ;
                        }
                        else if (buffer == "return") {
                            token = new Token(KT_RETURN, "return", line, col) ;
                        }
                        else if (buffer == "function") {
                            token = new Token(KT_FUNCTION, "function", line, col) ;
                        }
                    }
                    else {
                        token = new Token(VT_IDENT, buffer, line, col);
                    }
                    tokens.push_back(token);
                    buffer.clear();
                    this->step_back();
                }
                //TODO: Implement floating point numbers.
                else if (isdigit(this->current)) {
                    while (isdigit(this->current)) {
                        buffer.push_back(this->current);
                        this->advance();
                        col += 1;
                    }
                    token = new Token(VT_INT, buffer, line, col);
                    tokens.push_back(token);
                    buffer.clear();
                    this->step_back();
                }
                break;
        }
        this->advance();
        if (this->current == '\n') {
            line += 1;
            col = 0;
        }
        else if (this->current == '\t') {
            col += 4;
        }
        else if (this->current == ' ') {
            col += 1;
        }
    }
    col += 1;
    auto eof = new Token(T_EOF, '\0', line, col);
    tokens.push_back(eof);
    return tokens;
}

void Lexer::step_back() {
    this->index -= 1;
    this->current = this->text[this->index];
}
