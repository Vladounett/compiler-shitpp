#include "IRBuilder.hpp"
#include <algorithm>

IRBuilder::IRBuilder(std::vector<NodeStatementHandle> parsedProgram){
    this->parsedProgram = std::move(parsedProgram);
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
                // rien en IR
            },
            [this](NodeProgEnd&) {
                // rien en IR
            }
        }, ns);
}

bool IRBuilder::isVarAlreadyDeclared(std::string str) {
    return this->varTable.find(str) != this->varTable.end();
}
