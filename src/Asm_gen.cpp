#include "Asm_gen.hpp"

Asm_gen::Asm_gen(std::vector<Node_holder>& nodes_set, std::vector<std::string>& known_var_set){

    this->known_var = known_var_set;
    this->nodes = nodes_set;
    this->stack_size = 0;

}

std::string Asm_gen::build_asm(){

    std::stringstream asm_str;

    asm_str << "section .text\n";
    asm_str << "global _start\n";
    asm_str << "_start:\n";


    for(Node_holder &n : this->nodes){
        
        if(n.node_type == nodes_type::int_decl){
            asm_str << gen_node(n.int_decl.value());
        }

        if(n.node_type == nodes_type::ret){
            asm_str << gen_node(n.ret.value());
        }
    }

    return asm_str.str();

}

std::string Asm_gen::gen_node(Node_ret n){ //if we got a return node

    std::stringstream asm_str;

    asm_str << "    mov rax, 60\n" ;

    if(n.expr.is_var_ref){
        
        asm_str << "    mov rdi, " << "[rsp + " << ((this->stack_size-1-find_var_name_index(n.expr.var_ref.var_name))*8) << "]" << "\n";

    }else{

        if(n.expr.int_literal.getVal() == "0"){

            asm_str << "    xor rdi, rdi\n";

        }else{

            asm_str << "    mov rdi, " << n.expr.int_literal.getVal() << "\n";

        }
    }

    asm_str << "    syscall\n";

    return asm_str.str();

}

std::string Asm_gen::gen_node(Node_int_decl n){ //if we got an int declaration

    std::stringstream asm_str;

    if(n.expr.is_var_ref){
        
        asm_str << "    mov rax, " << "[rsp + " << ((this->stack_size-1-find_var_name_index(n.expr.var_ref.var_name))*8) << "]" << "\n";

    }else{
        asm_str << "    mov rax, " << n.expr.int_literal.getVal() << "\n";
    }

    asm_str << "    push rax\n";

    this->stack_size++;

    return asm_str.str();

}

short Asm_gen::find_var_name_index(std::string str){

    auto it = std::find(this->known_var.begin(), this->known_var.end(), str);

    if(it != this->known_var.end()){

        return std::distance(this->known_var.begin(), it);

    }else{

        std::cerr << "Error : asm_gen couldn't find var_name >> " << str << " << how is it even possible ????" << std::endl; 
        exit(EXIT_FAILURE);

    }

}