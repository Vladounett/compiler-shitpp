#ifndef GEN_DEF
#define GEN_DEF

#include "Nodes.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Asm_gen{

    public:

        Asm_gen(std::vector<NodeStatementHandle>& nodes);

        void build_asm();

        std::string getBuiltAsm();

    private:
        std::stringstream built_asm;
        std::vector<NodeStatementHandle> nodes;
        size_t stack_size;
        void genStatement(NodeStatement& ns);
        void genExpr(NodeExpr& ne);
        void write(std::string line, short indentIndex);
        int varDiscovery();

        std::unordered_map<std::string, VarInfo> varTable;
};



#endif