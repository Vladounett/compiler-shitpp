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

int main(int argc, char* argv[]){
    //If input invalid = error, we don't do anything
    if(argc != 2){
        std::cerr << "Error : invalid input" << std::endl;
        std::cerr << "Usage : s++ <input.shyt>" << std::endl;
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

    Tokenizer tokenizer = Tokenizer(totalStr);
    tokenizer.tokenize();
    std::cout << "----- tokens -----" << std::endl;
    tokenizer.debugTokens();

    //Now we parse it

    Parser parser = Parser(tokenizer.getTokens());
    parser.parse();
    std::cout << "----- parsedProgram -----" << std::endl;
    parser.debugParsedProgram();

    Asm_gen gen = Asm_gen(parser.getParsedProgram());
    gen.build_asm();
    std::cout << "----- builtASM -----" << std::endl;
    std::cout << gen.getBuiltAsm() << std::endl;

    File_Builder fb = File_Builder();
    fb.build_file(gen.getBuiltAsm());

    system("nasm -f elf64 output/finished_product.asm");
    system("ld output/finished_product.o -o output/finished_product.out");

    return 0;
}