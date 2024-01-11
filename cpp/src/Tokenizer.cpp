#include "Tokenizer.hpp"
#include "TokenType_Str.hpp"

Tokenizer::Tokenizer(std::string& str_set){
    this->str = str_set;
    this->flag_is_int_literal = false;
    this->last_char = ' ';
    //this->flag_is_word_correct = false;
    this->flag_space_decl = false;
    this->flag_word_found = false;
}

std::vector<Token> Tokenizer::getTokens(){
    return this->tokens;
}

void Tokenizer::push(char c){

    //std::cout << "char : " << c << std::endl;
    //std::cout << "last_char : " << last_char << std::endl;

    if(c == EOF){

        buffer.clear();
        std::cout << "char : EOF" << std::endl;

    }else if(std::isalpha(c)){ //if letter, if it was a space before, we know the word we are reading is not an int literal
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

        this->tokens.push_back(Token(TokenType::equal, "="));
        buffer.clear();
        this->last_char = c;

    }else if(std::isspace(c) || c == ';'){

        this->flag_word_found = false;

        //whitespace or semicolons detected, so we check if the previous word is a token type
        std::string word = convert_vector_to_string(buffer.data(), buffer.size());
        
        if(word == TOKENS_VALUES[VAL_OF_EXIT]){

            this->tokens.push_back(Token(TokenType::_return, "eexit"));
            this->flag_word_found = true;
            this->flag_space_decl = false;
            this->flag_is_int_literal = false;

        }else if(this->flag_is_int_literal){

            this->tokens.push_back(Token(TokenType::int_literal, word));
            this->flag_word_found = true;
            this->flag_space_decl = false;
            this->flag_is_int_literal = false;

        }else if(word == TOKENS_VALUES[VAL_OF_DECL]){

            this->tokens.push_back(Token(TokenType::int_decl, "i delcaree"));
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

                std::cerr << "Error : bad word >> " << word << " << wtf is that supposed to mean ???" << std::endl;
                exit(EXIT_FAILURE);

            }else{ //it could be a var_name so we verify if it could be a valid var_name then we create the token if yes, the parser will see himself if the syntax is valid or nah 

                if(word[0] != '\0' && !std::isdigit(word[0])){

                    this->tokens.push_back(Token(TokenType::var_name, word));

                    if(c == ';'){ //if its a semicolon, then we juste create a token semicolon
                        this->tokens.push_back(Token(TokenType::semi_col, ";"));
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
            this->tokens.push_back(Token(TokenType::semi_col, ";"));
            //std::cout << "semicolon" << std::endl;
            }

            this->last_char = c;
            buffer.clear();
        }

    }else{

        std::cerr << "Erreur : bad char >> " << c << " << wtf is this ??" << std::endl;
        exit(EXIT_FAILURE);

    }
}

//converting a vector<char>.data() to a string
std::string Tokenizer::convert_vector_to_string(char* to_convert, int vector_size){
    std::string res(to_convert, vector_size);
    return res;
}