#ifndef IR_BUILDER
#define IR_BUILDER

#include <unordered_map>
#include <string>
#include <vector>
#include "Nodes.hpp"
#include "IRNodes.hpp"

class IRBuilder{

    public:

        IRBuilder(std::vector<NodeStatementHandle> parsedProgram);
        void buildIR();

    private:
        std::vector<NodeStatementHandle> parsedProgram;
        std::unordered_map<std::string, VarInfo> varTable;

        bool isVarAlreadyDeclared(std::string str);
        void genStatement(NodeStatement& ns);
        void pushNode(IRNode in);
        void genReturn(NodeReturn& nr);
        void genIntDecl(NodeIntDecl& nid);
        void genExpr(NodeIntDecl& nid);
        void genExpr(NodeReturn& nr);
};

#endif