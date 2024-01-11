#include "Asm_gen.hpp"

Asm_gen::Asm_gen(std::vector<Node_holder> nodes_set, std::vector<std::string> known_var_set){

    this->known_var = known_var_set;
    this->nodes = nodes_set;

}

std::string Asm_gen::build_asm(){

    std::stringstream asm_str;

    asm_str << "global _start\n";
    asm_str << "_start:\n";

    for(Node_holder n : this->nodes){
        
        if(n.node_type == nodes_type::int_decl){
            asm_str << gen_node(n.int_decl);
        }

        if(n.node_type == nodes_type::ret){
            asm_str << gen_node(n.ret);
        }
    }

    return asm_str.str();

}

std::string Asm_gen::gen_node(Node_ret n){

    std::stringstream asm_str;

    asm_str << "    mov rax, 60\n" ;
    asm_str << "    mov rdi, " << n.expr.int_literal.getVal() << "\n";
    asm_str << "    syscall\n";

    return asm_str.str();

}

std::string Asm_gen::gen_node(Node_int_decl n){

    std::stringstream asm_str;

    asm_str << "    mov rax, " << n.expr.int_literal.getVal() << "\n";
    asm_str << "    push rax\n";

    return asm_str.str();

}