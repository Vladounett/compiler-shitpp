#ifndef TOKEN_DEF
#define TOKEN_DEF

#include "TokenType_Enum.hpp"
#include <string>


class Token{

    public:

        Token(TokenType type_set, std::string val_set);
        TokenType getType();
        std::string getVal();

    private:
        TokenType type;
        std::string val;
    
};

#endif