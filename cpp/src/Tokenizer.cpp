#include "Tokenizer.hpp"
#include "TokenType_Str.hpp"

Tokenizer::Tokenizer(std::string str_set){
    this->str = str_set;
    this->flag_is_int_literal = false;
    this->flag_have_been_whitespace = true;
    this->flag_have_been_digit = false;
}

std::vector<Token> Tokenizer::getTokens(){
    return this->tokens;
}

void Tokenizer::push(char c){
    if(std::isalpha(c)){ //if letter, if it was a space before, we know the word we are reading is not an int literal
                         //if it was not a space but a digit before then we know that what we are reading is not an int literal.
        buffer.push_back(c);

        if(this->flag_have_been_whitespace){

            this->flag_is_int_literal = false;
            this->flag_have_been_whitespace = false;

        }else if(this->flag_have_been_digit){

            this->flag_is_int_literal = false;

        }
        this->flag_have_been_digit = false;

    }else if(std::isdigit(c)){ //if is digit, if char before was a space then maybe we are reading an int literal, so we change the flag to true

        buffer.push_back(c);

        if(this->flag_have_been_whitespace){

            this->flag_is_int_literal = true;
            this->flag_have_been_whitespace = false;
            
        }
        this->flag_have_been_digit = true;

    }else if(std::isspace(c) || c == ';'){

        //whitespace or semicolons detected, so we check if the previous word is a token type, then we empty the buffer
        std::string word = convert_vector_to_string(buffer.data(), buffer.size());
        
        if(word == TOKENS_VALUES[VAL_OF_RETURN]){
            this->tokens.push_back(Token(TokenType::_return, "return"));
        }
        else if(this->flag_is_int_literal){
            this->tokens.push_back(Token(TokenType::int_literal, word));
        }

        if(c == ';'){
            this->tokens.push_back(Token(TokenType::semi_col, ";"));
        }else{
            this->flag_have_been_whitespace = true;
        }

        buffer.clear();
    }
}

//converting a vector<char>.data() to a string
std::string Tokenizer::convert_vector_to_string(char* to_convert, int vector_size){
    std::string res(to_convert, vector_size);
    return res;
}