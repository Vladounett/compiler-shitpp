#ifndef TOKEN_DEF
#define TOKEN_DEF

#include "TokenType_Enum.hpp"
#include <string>


class Token{

    public:

        Token();
        Token(TokenType type_set, std::string val_set, short columnIndex, short lineIndex);
        TokenType getType();
        std::string getVal();
        short getColumnIndex();
        short getLineIndex();

    private:
        TokenType type;
        std::string val;
        short columnIndex;
        short lineIndex;
};

#endif