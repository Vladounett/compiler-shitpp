#include "Token.hpp"

Token::Token(){
    this->type = TokenType::null;
    this->val = "";
    this->lineIndex = 0;
    this->columnIndex = 0;
}

Token::Token(TokenType type_set, std::string val_set, short lineIndex, short columnIndex){
    this->type = type_set;
    this->val = val_set;
    this->lineIndex = lineIndex;
    this->columnIndex = columnIndex;
}

TokenType Token::getType(){
    return this->type;
}

std::string Token::getVal(){
    return this->val;
}

short Token::getColumnIndex(){
    return this->columnIndex;
}

short Token::getLineIndex(){
    return this->lineIndex;
}