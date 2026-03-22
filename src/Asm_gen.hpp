#ifndef GEN_DEF
#define GEN_DEF

#include "Nodes.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "IRNodes.hpp"

class Asm_gen {
public:
    Asm_gen(std::vector<IRNode> IR);
    void build_asm();
    std::string getBuiltAsm();

private:
    std::stringstream built_asm;
    std::vector<IRNode> IR;

    std::unordered_map<std::string, int> varOffsets;
    std::unordered_map<int, int> tempOffsets; 
    
    int totalStackSize = 0;

    void write(std::string line, short indentIndex);
    void resolveMemoryLayout();
};



#endif