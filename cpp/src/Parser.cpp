#include "Parser.hpp"

Parser::Parser(std::vector<Token> tokens_set){
    this->tokens = tokens_set;
    this->current_index = 0;
}

void Parser::parse(){

    const int size_tokens_vec = this->tokens.size();

    while(tokens_current_token_exist()){

        if(get_token().getType() == TokenType::_return){

            Node_ret node_ret = Node_ret();

            node_ret.expr = parse_expr();

            Node_holder node_hold = Node_holder(nodes_type::ret);
            node_hold.ret = node_ret;

            std::cout << "la val : " << node_hold.ret.expr.int_literal.getVal() << std::endl;

            this->nodes.push_back(node_hold);

        }

    }

}

Node_expr Parser::parse_expr(){

    Node_expr res;
    res.node_type = nodes_type::expr;

    Token current_t = get_token();

    if(current_t.getType() == TokenType::int_literal){
        res.int_literal = current_t;
    }

    if(res.int_literal.getType() == TokenType::null){
        exit(EXIT_FAILURE);
    }

    return res;

}

Token Parser::get_token(){
    
    Token res = this->tokens.at(this->current_index);
    this->current_index++;
    return res;

}

bool Parser::tokens_current_token_exist(){

    if(this->current_index < this->tokens.size()){
        return true;
    }else{
        return false;
    }

}

std::vector<Node_holder> Parser::get_nodes(){
    return this->nodes;
}

std::string Parser::build_asm(){
    std::stringstream res;
    res << "global _start\n";
    res << "_start:\n";

    for(Node_holder n : this->nodes){
        
        if(n.node_type == nodes_type::ret){
            res << "    mov rax, 60\n" ;
            res << "    mov rdi, " << n.ret.expr.int_literal.getVal() << "\n";
            res << "    syscall\n";
        }
    }

    return res.str();
}