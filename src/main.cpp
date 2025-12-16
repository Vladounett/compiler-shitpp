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
#include "Asm_gen.hpp"

//Defining a function that will tokenize the file
Tokenizer find_tokens(std::string& str){

    Tokenizer tokenizer = Tokenizer(str);

    for(char c : str){
        if(c != EOF){
            tokenizer.push(c);
        }
    }

    return tokenizer;
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

    Tokenizer tokenizer = find_tokens(totalStr);
    std::vector<Token> valid_tokens = tokenizer.getTokens();
    std::vector<short> no_tokens_line = tokenizer.getNo_token_line();

    //Now we parse it

    /*for(Token t : valid_tokens){
        std::cout << "token : " << t.getVal() << std::endl;
    }*/

    Parser parser = Parser(valid_tokens, no_tokens_line);

    parser.parse();

    Asm_gen gen = Asm_gen(*parser.get_nodes(), *parser.get_known_var());

    std::string asm_str = gen.build_asm();

    std::cout << asm_str << std::endl;

    File_Builder fb = File_Builder();
    fb.build_file(asm_str);

    system("nasm -f elf64 output/finished_product.asm");
    system("ld output/finished_product.o -o output/finished_product");

    return 0;
}