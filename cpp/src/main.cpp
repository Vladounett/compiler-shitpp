#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "TokenType_Enum.hpp"
#include "TokenType_Str.hpp"
#include "File_Builder.hpp"

//converting a vector<char>.data() to a string
std::string convert_vector_to_string(char* to_convert, int vector_size){
    std::string res(to_convert, vector_size);
    return res;
}

//Defining a vector that will tokenize the file
std::vector<Token> find_tokens(std::string& str){

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


//OUTDATED --> SHOULD DO PARSE TREE
std::string building_asm(std::vector<Token>& tokens){

    std::stringstream res;

    res << "global _start\n";
    res << "_start:\n";

    for(int i = 0; i < tokens.size(); i++){
        Token t = tokens.at(i);

        if(t.getType() == TokenType::_return && i + 2 < tokens.size()){
            if(tokens.at(i + 1).getType() == TokenType::int_literal && tokens.at(i + 2).getType() == TokenType::semi_col){
                res << "    mov rax, 60\n";
                res << "    mov rdi, " << tokens.at(i+1).getVal() << '\n';
                res << "    syscall\n";
            }
        }
    }


    return res.str();
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

    std::vector<Token> valid_tokens = find_tokens(totalStr);
    std::cout << building_asm(valid_tokens) << std::endl;

    File_Builder fb = File_Builder();
    fb.build_file(building_asm(valid_tokens));

    system("nasm -f elf64 output/finished_product.asm");
    system("ld output/finished_product.o -o output/finished_product");

    return 0;
}