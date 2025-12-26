#ifndef TOKENIZER_DEF
#define TOKENIZER_DEF

#include <iostream>
#include <string>
#include <vector>
#include "Token.hpp"

class Tokenizer{
    public:
        Tokenizer(std::string& str_set);
        std::vector<Token> getTokens();
        void push(char c);
        void debugTokens();
        void tokenize();

    private:

        void push_token(Token token_p);
        std::string convert_vector_to_string(char* to_convert, int vector_size);
        std::string str;
        std::vector<Token> tokens;
        std::vector<char> buffer;
        bool flag_is_int_literal;
        //bool flag_is_word_correct;
        bool flag_space_decl;
        bool flag_word_found;
        char last_char;
        short line_counter;
        short tokens_on_line;

};

#endif