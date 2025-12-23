#ifndef TOKENSTYPE_ENUM
#define TOKENSTYPE_ENUM

enum class TokenType{
    _return,
    int_literal,
    semi_col,
    int_decl,
    var_name,
    equal,
    null
};

inline std::string toString(TokenType t){
    switch(t){
        case TokenType::_return: return ""; break;
    }
}

#endif