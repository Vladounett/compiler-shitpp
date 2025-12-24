#ifndef TOKENSTYPEMAP_ENUM
#define TOKENSTYPEMAP_ENUM

#include <string>
#include <unordered_map>
#include "TokenType_Enum.hpp"

//Key words, but i have clumsy fingers

inline const std::unordered_map<TokenType, std::string> TOKENS_VALUES = {
    {TokenType::_return, "i am leaving"},
    {TokenType::int_decl, "i declare"},
    {TokenType::line_ender, "!"}
};

#endif