#include "Asm_gen.hpp"
#include <variant>

Asm_gen::Asm_gen(std::vector<NodeStatementHandle>& nodes){

    this->nodes = std::move(nodes);
    this->stack_size = 0;

}

void Asm_gen::build_asm(){

    int totalOffset = this->varDiscovery();

    write("BITS 64", 0);
    write("section .text", 0);
    write("global _start", 0);
    write("_start:", 0);

    write("push rbp", 1);
    write("mov rbp, rsp", 1);
    write("sub rsp, " + std::to_string(totalOffset), 1);

    for(NodeStatementHandle& nsh : this->nodes){
        write("", 1);
        genStatement(*nsh);
    }
}

void Asm_gen::genStatement(NodeStatement& ns){
    std::visit(overload{
        [this](NodeReturn& ret) {
            genExpr(*ret.val);
            write("mov rdi, rax", 1);
            write("mov rax, 60", 1);
            write("syscall", 1);
        },
        [this](NodeIntDecl& decl) {
            genExpr(*decl.val);
            write("mov qword [rbp - " + std::to_string(this->varTable[decl.var_name].offset) + "], rax", 1);
            this->stack_size++;
        }
    }, ns);
}

void Asm_gen::genExpr(NodeExpr& ne){
    std::visit(overload{
        [this](NodeVarRef& varRef) {
            write("mov rax, [rbp - " + std::to_string(this->varTable[varRef.var_name].offset) + "]", 1);
        },
        [this](NodeIntLiteral& intLit) {
            write("mov rax, " + std::to_string(intLit.val), 1);
        }
    }, ne);
}

void Asm_gen::write(std::string line, short indentIndex){
    indentIndex *= 4;
    std::string indent(indentIndex, ' ');
    this->built_asm << indent << line << std::endl;
}

std::string Asm_gen::getBuiltAsm(){
    return this->built_asm.str();
}

int Asm_gen::varDiscovery(){
    int offset = 0;

    for(NodeStatementHandle& nsh : this->nodes){
        std::visit(overload{
            [&](NodeReturn& ret) {},
            [this, &offset](NodeIntDecl& decl) {offset+=8; this->varTable[decl.var_name] = {offset};}
        }, *nsh);
    }

    if(offset % 16 != 0){
        offset += 8;
    }

    return offset;
}