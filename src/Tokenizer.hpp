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
        std::vector<short> getNo_token_line();
        void push(char c);

    private:

        void push_token(Token token_p);
        std::string convert_vector_to_string(char* to_convert, int vector_size);
        std::string str;
        std::vector<Token> tokens;
        std::vector<char> buffer;
        std::vector<short> no_tokens_line; //represent the number of tokens per line; exemple : {3, 8, 2, 6} means, 3 tokens on the first line, 8 tokens on the seconds line, etc...
        bool flag_is_int_literal;
        //bool flag_is_word_correct;
        bool flag_space_decl;
        bool flag_word_found;
        char last_char;
        short line_counter;
        short tokens_on_line;

};

#endif