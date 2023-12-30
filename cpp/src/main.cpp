#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "TokenType_Enum.hpp"
#include "Tokenizer.hpp"
#include "File_Builder.hpp"
#include "Parser.hpp"

//Defining a vector that will tokenize the file
std::vector<Token> find_tokens(std::string& str){

    Tokenizer tokenizer = Tokenizer(str);

    for(char c : str){
        if(c != EOF){
            tokenizer.push(c);
        }
    }

    return tokenizer.getTokens();
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
    Parser parser = Parser(valid_tokens);

    parser.parse();
    std::string asm_str = parser.build_asm();

    std::cout << asm_str << std::endl;

    File_Builder fb = File_Builder();
    fb.build_file(asm_str);

    system("nasm -f elf64 output/finished_product.asm");
    system("ld output/finished_product.o -o output/finished_product");

    return 0;
}