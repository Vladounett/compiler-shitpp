#include "Token.hpp"

Token::Token(TokenType type_set, std::string val_set){
    this->type = type_set;
    this->val = val_set;
}

TokenType Token::getType(){
    return this->type;
}

std::string Token::getVal(){
    return this->val;
}