#include "Tokenizer.hpp"
#include "TokenType_Map.hpp"

Tokenizer::Tokenizer(std::string &str_set){
    this->str = str_set;
    this->flag_is_int_literal = false;
    this->last_char = ' ';
    //this->flag_is_word_correct = false;
    this->flag_space_decl = false;
    this->flag_word_found = false;
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

    if(std::isalpha(c) && c != 10){ //if letter, if it was a space before, we know the word we are reading is not an int literal
                         //if it was not a space but a digit before then we know that what we are reading is not an int literal.
        buffer.push_back(c);

        if(std::isspace(this->last_char)){

            this->flag_is_int_literal = false;

        }else if(std::isdigit(this->last_char)){

            this->flag_is_int_literal = false;

        }

        this->last_char = c;

    }else if(std::isdigit(c)){ //if is digit, if char before was a space then maybe we are reading an int literal, so we change the flag to true

        buffer.push_back(c);

        if(std::isspace(this->last_char)){

            this->flag_is_int_literal = true;
            
        }

        this->last_char = c;

    }else if(c == '='){ //if it's an equal we get a equal token

        //this->tokens.push_back(Token(TokenType::equal, "="));
        push_token(Token(TokenType::equal, "=", this->line_counter, this->tokens_on_line));
        buffer.clear();
        this->last_char = c;

    }else if(std::isspace(c) && c != 10 || c == ';'){

        this->flag_word_found = false;

        //whitespace or semicolons detected, so we check if the previous word is a token type
        std::string word = convert_vector_to_string(buffer.data(), buffer.size());
        
        if(word == TOKENS_VALUES.at(TokenType::_return)){

            //this->tokens.push_back(Token(TokenType::_return, "eexit"));
            push_token(Token(TokenType::_return, "eexit", this->line_counter, this->tokens_on_line));
            this->flag_word_found = true;
            this->flag_space_decl = false;
            this->flag_is_int_literal = false;

        }else if(this->flag_is_int_literal){

            //this->tokens.push_back(Token(TokenType::int_literal, word));
            push_token(Token(TokenType::int_literal, word, this->line_counter, this->tokens_on_line));
            this->flag_word_found = true;
            this->flag_space_decl = false;
            this->flag_is_int_literal = false;

        }else if(word == TOKENS_VALUES.at(TokenType::int_decl)){

            //this->tokens.push_back(Token(TokenType::int_decl, "i delcaree"));
            push_token(Token(TokenType::int_decl, "i delcaree", this->line_counter, this->tokens_on_line));
            this->flag_word_found = true;
            this->flag_space_decl = false;
            this->flag_is_int_literal = false;

        }
        
        //If it was not a recongnized word, we verifiy :
        if(!this->flag_word_found){

            if(this->last_char == 'i' && !this->flag_space_decl){ //if last char was a i then we dont clear the buffer, beacuse it could be the keyword "i delcaree"

                buffer.push_back(' ');
                this->last_char = c;
                this->flag_space_decl = true;

            }else if(this->flag_space_decl){ //if we already skipped clearing the buffer last time it was a space, then we throw an error because it mean it is not a recognized word

                std::cerr << "Error : bad word >> " << word << " << what is that supposed to mean ?" << std::endl;
                std::cerr << "at line : " << this->line_counter+1 << ", word : " << this->tokens_on_line+1 << std::endl;
                exit(EXIT_FAILURE);

            }else{ //it could be a var_name so we verify if it could be a valid var_name then we create the token if yes, the parser will see himself if the syntax is valid or nah 

                if(word[0] != '\0' && !std::isdigit(word[0])){

                    this->tokens.push_back(Token(TokenType::var_name, word, this->line_counter, this->tokens_on_line));

                    if(c == ';'){ //if its a semicolon, then we juste create a token semicolon
                        //this->tokens.push_back(Token(TokenType::semi_col, ";"));
                        push_token(Token(TokenType::semi_col, ";", this->line_counter, this->tokens_on_line));
                        //std::cout << "semicolon" << std::endl;
                    }
                    
                    buffer.clear();
                    this->last_char = c;
                    //std::cout << "var_name : " << word[0] /*static_cast<int>(word[0])*/ << std::endl;

                }else{
                    buffer.clear();
                    this->last_char = c;
                }

            }

        }else{ //if it was recognized, then we just store c in the last char, and clear the buffer

            if(c == ';'){ //if its a semicolon, then we juste create a token semicolon
            this->tokens.push_back(Token(TokenType::semi_col, ";", this->line_counter, this->tokens_on_line));
            //std::cout << "semicolon" << std::endl;
            }

            this->last_char = c;
            buffer.clear();

        }

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