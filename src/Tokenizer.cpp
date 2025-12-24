#include "Tokenizer.hpp"
#include "TokenType_Map.hpp"

Tokenizer::Tokenizer(std::string &str_set){
    this->str = str_set;
    this->flag_is_int_literal = false;
    this->last_char = ' ';
    this->line_counter = 1;
    this->tokens_on_line = 0;
}

std::vector<Token> Tokenizer::getTokens(){
    return this->tokens;
}

void Tokenizer::push(char c){

    //std::cout << "char c : " << c << ", (int) char c : " << (int) c << std::endl;
    //std::cout << "char : " << c << std::endl;
    //std::cout << "last_char : " << last_char << std::endl;

    if(std::isalpha(c) && c != 10){ //if is a letter, we push it and flag it as a non int_literal

        buffer.push_back(c);
        this->flag_is_int_literal = false;
        this->last_char = c;

    }else if(std::isdigit(c)){ //if it is a digit, if the previous char was a space then it starts with a digit so we flag it as an int_literal
        
        buffer.push_back(c);
        if(std::isspace(this->last_char)){
            this->flag_is_int_literal = true;
        }
        this->last_char = c;

    }else if(std::isspace(c) && c != 10 || c == TOKENS_VALUES.at(TokenType::line_ender)[0] || c == '='){
        std::string word = convert_vector_to_string(buffer.data(), buffer.size());
        //if word is not empty, we check if it is an int_literal, if it is next to an equal sign, or we push it as it is
        if(word != ""){
            if(flag_is_int_literal){
                //std::cout << "pushing : " + word << std::endl;
                push_token(Token(TokenType::int_literal, word, this->line_counter, this->tokens_on_line));
            }else if(c == '='){
                push_token(Token(TokenType::identifier, word, this->line_counter, this->tokens_on_line));
                push_token(Token(TokenType::equal, "=", this->line_counter, this->tokens_on_line));
            }else{
                //std::cout << "pushing : " + word << std::endl;
                push_token(Token(TokenType::identifier, word, this->line_counter, this->tokens_on_line));
            }
        }else{ //if word is empty we check if it is because the char was an equal sign
            if(c == '='){
                push_token(Token(TokenType::equal, "=", this->line_counter, this->tokens_on_line));
            }
        }

        if(c == TOKENS_VALUES.at(TokenType::line_ender)[0]){ //if it is an line_ender we push a line_ender token
            push_token(Token(TokenType::line_ender, TOKENS_VALUES.at(TokenType::line_ender), this->line_counter, this->tokens_on_line)); 
        }

        this->last_char = c;
        buffer.clear();
    }else if(c == 10){
        this->line_counter++;
        this->tokens_on_line = 0;
    }else{
        std::cerr << "Error : bad char >> " << c << " << what is this ?" << std::endl;
        exit(EXIT_FAILURE);
    }
}

//converting a vector<char>.data() to a string
std::string Tokenizer::convert_vector_to_string(char* to_convert, int vector_size){
    std::string res(to_convert, vector_size);
    return res;
}

void Tokenizer::push_token(Token token_p){
    this->tokens.push_back(token_p);
    this->tokens_on_line++;
}

void Tokenizer::debugTokens(){ //debug the tokens in the console
    for(Token &t : this->tokens){
        if(t.getType() == TokenType::line_ender){
            std::cout << t.getVal() + "(" + typeToString(t.getType()) + ")" << std::endl;
        }else{
            std::cout << t.getVal() + "(" + typeToString(t.getType()) + ") ";
        }
    }
}