#ifndef TOKENSTYPESTR_ENUM
#define TOKENSTYPESTR_ENUM

#define VAL_OF_RETURN 0

#include <string>
#include <array>

class TokenType_Str{

    public:
        TokenType_Str();
        std::array<std::string, 2> tokens_values = {"return", "test"};

};

#endif