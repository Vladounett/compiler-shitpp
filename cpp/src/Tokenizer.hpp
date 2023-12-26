#ifndef TOKENIZER_DEF
#define TOKENIZER_DEF

#include <iostream>
#include <string>
#include <vector>
#include "Token.hpp"

class Tokenizer{
    public:
        Tokenizer(std::string str_set);
        std::vector<Token> getTokens();
        void push(char c);

    private:
        std::string convert_vector_to_string(char* to_convert, int vector_size);
        std::string str;
        std::vector<Token> tokens;
        std::vector<char> buffer;
        bool flag_is_int_literal;
        bool flag_have_been_whitespace;
        bool flag_have_been_digit;

};

#endif