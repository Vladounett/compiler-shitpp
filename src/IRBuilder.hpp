#ifndef IR_BUILDER
#define IR_BUILDER

#include <unordered_map>
#include <string>
#include <vector>
#include "Nodes.hpp"
#include "IRNodes.hpp"

class IRBuilder{

    public:

        IRBuilder(std::vector<NodeStatementHandle>& parsedProgram);
        void buildIR();
        void debugIR();

    private:
        std::vector<NodeStatementHandle>& parsedProgram;
        std::unordered_map<std::string, VarInfo> varTable;
        std::vector<IRNode> IR;

        bool isVarAlreadyDeclared(std::string str);
        void genStatement(NodeStatement& ns);
        void pushNode(IRNode in);
        void genReturn(NodeReturn& nr);
        void genIntDecl(NodeIntDecl& nid);
        int genExpr(NodeExpr& expr);
        int genIntLiteral(NodeIntLiteral& lit);
        int genVarRef(NodeVarRef& ref);

        int newTempVar();

        int currentVarTemp;

        std::string irToString(IRop op);
};

#endif