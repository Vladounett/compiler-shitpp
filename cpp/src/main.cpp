#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "TokenType_Enum.hpp"
#include "TokenType_Str.hpp"

//converting a vector<char>.data() to a string
std::string convert_vector_to_string(char* to_convert, int vector_size){
    std::string res(to_convert, vector_size);
    return res;
}

//Defining a vector that will tokenize the file
std::vector<Token> tokens(std::string& str){

    TokenType_Str tokens_str = TokenType_Str();

    std::vector<Token> res;

    std::vector<char> buffer;

    bool is_int_literal = false;
    bool have_been_whitespace = false;

    for(char c : str){

        if(std::isalpha(c)){ //if letter
            buffer.push_back(c);
            if(have_been_whitespace){
                is_int_literal = false;
            }
        }
        else if(std::isdigit(c)){ //if is digit
            buffer.push_back(c);
            if(have_been_whitespace){
                is_int_literal = true;
            }
        }
        else if(std::isspace(c) || c == ';'){
            //whitespace or semicolons detected, so we check if the previous word is a token type, then we empty the buffer
            std::string word = convert_vector_to_string(buffer.data(), buffer.size());
            
            if(word == tokens_str.tokens_values[VAL_OF_RETURN]){
                res.push_back(Token(TokenType::_return, "return"));
            }
            else if(is_int_literal){
                res.push_back(Token(TokenType::int_literal, word));
            }

            if(c == ';'){
                res.push_back(Token(TokenType::semi_col, ";"));
            }else{
                have_been_whitespace = true;
            }

            buffer.clear();
        }
    }


    return res;
}


int main(int argc, char* argv[]){

    //If input invalid = error, we don't do anything
    if(argc != 2){

        std::cerr << "Error : invalid input" << std::endl;
        std::cerr << "Usage : shit++ <input.shyt>" << std::endl;
        return 1;

    }

    //else we do things


    //trying to read the specified file
    std::fstream fileToRead(argv[1]);
    std::string totalStr;

    if(fileToRead.is_open()){ //if we can access the file, we read it, get it into a string

        std::stringstream total;
        
        std::string line;

        while(std::getline(fileToRead, line)){
            total << line << '\n';
        }

        totalStr = total.str();

        fileToRead.close();

    }else{ //else we quit bc, no file = error

        std::cerr << "Error : can't read file" << std::endl;
        std::cerr << "Make sure your file path is correct" << std::endl;
        return 1;

    }

    //we got a string, now we want tokens
    //so let's get tokens

    std::vector<Token> valid_tokens = tokens(totalStr);

    for(Token t : valid_tokens){
        std::cout << t.getVal() << std::endl;
    }

    return 0;
}