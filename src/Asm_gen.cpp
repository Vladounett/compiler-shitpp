#include "Asm_gen.hpp"
#include <variant>

Asm_gen::Asm_gen(std::vector<IRNode> IR) : IR(std::move(IR)) {}

void Asm_gen::resolveMemoryLayout() {
    int currentOffset = 0;
    for (const auto& node : IR) {
        if (!node.var.empty() && varOffsets.find(node.var) == varOffsets.end()) {
            currentOffset += 8;
            varOffsets[node.var] = currentOffset;
        }
        if (node.op == IRop::LoadConst || node.op == IRop::LoadVar) {
            if (tempOffsets.find(node.var_dst) == tempOffsets.end()) {
                currentOffset += 8;
                tempOffsets[node.var_dst] = currentOffset;
            }
        }
    }
    // 16-bytes alignement
    if (currentOffset % 16 != 0) currentOffset += 8;
    this->totalStackSize = currentOffset;
}

void Asm_gen::build_asm() {
    resolveMemoryLayout();

    write("BITS 64", 0);
    write("section .text", 0);
    write("global _start", 0);
    write("_start:", 0);
    write("push rbp", 1);
    write("mov rbp, rsp", 1);
    write("sub rsp, " + std::to_string(totalStackSize), 1);

    for (const auto& n : IR) {
        switch (n.op) {
            case IRop::LoadConst:
                write("mov rax, " + std::to_string(n.immediate_val), 1);
                write("mov qword [rbp - " + std::to_string(tempOffsets[n.var_dst]) + "], rax", 1);
                break;

            case IRop::LoadVar:
                write("mov rax, [rbp - " + std::to_string(varOffsets[n.var]) + "]", 1);
                write("mov qword [rbp - " + std::to_string(tempOffsets[n.var_dst]) + "], rax", 1);
                break;

            case IRop::StoreVar:
                write("mov rax, [rbp - " + std::to_string(tempOffsets[n.var_src]) + "]", 1);
                write("mov [rbp - " + std::to_string(varOffsets[n.var]) + "], rax", 1);
                break;

            case IRop::Return:
                write("mov rdi, [rbp - " + std::to_string(tempOffsets[n.var_src]) + "]", 1);
                write("mov rax, 60", 1);
                write("syscall", 1);
                break;
        }
    }
}

void Asm_gen::write(std::string line, short indentIndex) {
    std::string indent(indentIndex * 4, ' ');
    this->built_asm << indent << line << "\n";
}

std::string Asm_gen::getBuiltAsm() {
    return this->built_asm.str();
}