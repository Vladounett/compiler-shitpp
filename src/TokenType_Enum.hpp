#ifndef TOKENSTYPE_ENUM
#define TOKENSTYPE_ENUM

#include <string>

enum class TokenType{
    _return,
    int_literal,
    int_decl,
    line_ender,
    identifier,
    equal,
    null
};

inline std::string typeToString(TokenType t){
    switch(t){
        case TokenType::_return: return "return";
        case TokenType::int_decl: return "int_decl";
        case TokenType::identifier: return "identifier";
        case TokenType::null: return "null";
        case TokenType::equal: return "=";
        case TokenType::line_ender: return "!";
        case TokenType::int_literal: return "int_literal";
    }
    return "unknown_type";
};

#endif