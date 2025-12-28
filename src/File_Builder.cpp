#include "File_Builder.hpp"
#include <fstream>
#include <iostream>

File_Builder::File_Builder(){

}

void File_Builder::build_file(std::string to_build){

    std::ofstream file("output/finished_product.asm");
    if(file.is_open()){
        
        file << to_build;
        file.close();
        
    }else{
        std::cerr << "ERROR ON FILE BUILDER" << std::endl;
    }
}