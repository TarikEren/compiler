#ifndef COMPILER_TOKEN_HPP
#define COMPILER_TOKEN_HPP

#include <string>

typedef enum TokenTypes{
    //VT -> Value Type
    //KT -> Keyword Type
    //ET -> Escape Character Type
    //T  -> Other

    //Keywords
    KT_INT,         //int
    KT_CHAR,        //char
    KT_STRING,      //string
    KT_BOOL,        //bool
    KT_RETURN,      //return
    KT_IF,          //if
    KT_ELSE,        //else
    KT_FOR,         //for
    KT_DO,          //do
    KT_WHILE,       //while
    KT_BREAK,       //break

    //Values
    VT_INT,         //Integer values
    VT_CHAR,        //Character values
    VT_BOOL,        //Boolean values
    VT_STRING,      //String values
    VT_IDENT,       //Identifiers (i.e. function and variable names)

    //Other
    T_BANG,         //!
    T_EQUAL,        //=
    T_L_ANGLE,      //<
    T_R_ANGLE,      //>
    T_PLUS,         //+
    T_MINUS,        //-
    T_SLASH,        /*/*/
    T_STAR,         //*
    T_COLON,        //:
    T_MODULO,       //%
    T_AMPER,        //&
    T_L_PAR,        //(
    T_R_PAR,        //)
    T_L_BRACE,      //{
    T_R_BRACE,      //}
    T_L_BRACKET,    //[
    T_R_BRACKET,    //]
    T_SEMI,         //;
    T_PIPE,         //|
    T_QUOT,         //"
    T_HASH,         //#
    T_BACKSLASH,    /*\*/
    T_EOF,          //End of file

    //Multiple chars
    T_IS,           //==
    T_IS_NOT,       //!=
    T_LESS_EQ,      //<=
    T_GREATER_EQ,   //>=
    T_INCR,         //+=
    T_DECR,         //-=
    T_AND,          //&&
    T_OR,           //||
    T_COMMENT,      /*//*/

}TokenType;

class Token {
private:
    TokenType type{};
    std::string value{};
public:
    //Default constructor
    explicit Token() = default;

    //Constructor
    Token(TokenType new_type, const std::string& new_value) {
        this->type = new_type;
        this->value = new_value;
    }

    Token(TokenType new_type, char new_value) {
        this->type = new_type;
        this->value = new_value;
    }

    //Sets a provided token's type and value. Used for tokens with multiple characters.
    void set_token(TokenType, const std::string&);

    //Sets the token's type and value. Used for singular character tokens.
    void set_token(TokenType, char);

    //Sets the token's type.
    void set_token_type(TokenType);

    //Sets the token's value.
    void set_token_value(const std::string&);

    //Presents the token's properties as a string.
    static std::string token_to_string(Token*);
};

#endif