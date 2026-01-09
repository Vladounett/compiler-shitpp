#include "IRBuilder.hpp"
#include <algorithm>
#include <iostream>

IRBuilder::IRBuilder(std::vector<NodeStatementHandle>& parsedProgram) : parsedProgram(parsedProgram){
    this->currentVarTemp = 0;
}

void IRBuilder::buildIR(){
    for(NodeStatementHandle& nsh : this->parsedProgram){
        genStatement(*nsh);
    }
}

void IRBuilder::genStatement(NodeStatement& ns){
    std::visit(overload{
            [this](NodeIntDecl& decl) {
                genIntDecl(decl);
            },
            [this](NodeReturn& ret) {
                genReturn(ret);
            },
            [this](NodeProgStart&) {
            },
            [this](NodeProgEnd&) {
            }
        }, ns);
}

void IRBuilder::genIntDecl(NodeIntDecl& decl){
    if(isVarAlreadyDeclared(decl.var_name)){
        std::cerr << "Var already declared : " << decl.var_name << std::endl;
        exit(EXIT_FAILURE);
    }

    int value = genExpr(*decl.val);

    this->varTable[decl.var_name] = {};
    
    this->IR.push_back(IRNode{
        .op = IRop::StoreVar,
        .var_src = value,
        .var = decl.var_name
    });
}

void IRBuilder::genReturn(NodeReturn& ret){
    int value = genExpr(*ret.val);
    this->IR.push_back(IRNode{
        .op = IRop::Return,
        .var_src = value
    });
}

int IRBuilder::genExpr(NodeExpr& expr){
    return std::visit(overload{
        [this](NodeIntLiteral& nil){
            return genIntLiteral(nil);
        },
        [this](NodeVarRef& nvr){
            return genVarRef(nvr);
        }
    }, expr);
}

int IRBuilder::genIntLiteral(NodeIntLiteral& lit) {
    int t = newTempVar();
    this->IR.push_back(IRNode{
        .op  = IRop::LoadConst,
        .var_dst = t,
        .immediate_val = lit.val
    });
    return t;
}

int IRBuilder::genVarRef(NodeVarRef& ref) {
    if (!isVarAlreadyDeclared(ref.var_name)) {
        std::cerr << "Unknown var : " << ref.var_name << std::endl;
        exit(EXIT_FAILURE);
    }
    int t = newTempVar();
    this->IR.push_back(IRNode{
        .op  = IRop::LoadVar,
        .var_dst = t,
        .var = ref.var_name
    });
    return t;
}

int IRBuilder::newTempVar(){
    return this->currentVarTemp++;
}

bool IRBuilder::isVarAlreadyDeclared(std::string str) {
    return this->varTable.find(str) != this->varTable.end();
}

void IRBuilder::debugIR() {
    std::cout << "\n===== IR debug =====\n";
    int pc = 0;
    for (const IRNode& n : this->IR) {
        std::cout << pc++ << ": ";
        switch (n.op) {
            case IRop::LoadConst:
                std::cout << "t" << n.var_dst
                          << " = load_const "
                          << n.immediate_val;
                break;
            case IRop::LoadVar:
                std::cout << "t" << n.var_dst
                          << " = load_var "
                          << n.var;
                break;
            case IRop::StoreVar:
                std::cout << "store_var "
                          << n.var
                          << ", t" << n.var_src;
                break;
            case IRop::Return:
                std::cout << "return t"
                          << n.var_src;
                break;
        }
        std::cout << '\n';
    }
    std::cout << "===================\n";
}

std::string irToString(IRop op) {
    switch (op) {
        case IRop::LoadConst: return "load_const";
        case IRop::LoadVar:   return "load_var";
        case IRop::StoreVar:  return "store_var";
        case IRop::Return:    return "return";
        default:              return "unknown";
    }
}
