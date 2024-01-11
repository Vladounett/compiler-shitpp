#include "Parser.hpp"

Parser::Parser(std::vector<Token>& tokens_set){
    this->tokens = tokens_set;
    this->current_index = 0;
}

//Parse with the tokens given

void Parser::parse(){

    while(tokens_current_token_exist()){

        Token t = get_token();
        //std::cout <<t.getVal() << std::endl;

        if(t.getType() == TokenType::_return){

            Node_ret node_ret = Node_ret();

            //Try to parse an expression with the next token in the vector
            node_ret.expr = parse_expr();

            Node_holder node_hold = Node_holder(nodes_type::ret);
            node_hold.ret = node_ret;

            this->nodes.push_back(node_hold);

        }else if(t.getType() == TokenType::int_decl){

            if(this->current_index + 1 > this->tokens.size()){
                std::cerr << "Error : parser out of range" << std::endl;
                exit(EXIT_FAILURE);
            }

            Token nextToken_var_name = get_token();

            if(nextToken_var_name.getType() != TokenType::var_name){ //we got a key word to declare an int, so now we check if the next token is a var_name, if not we quit
                std::cerr << "Error : var name expected >> " << nextToken_var_name.getVal() << " << huh huh ??" << std::endl;
                exit(EXIT_FAILURE);
            }

            Token nextToken_equal = get_token();

            if(nextToken_equal.getType() != TokenType::equal){
                std::cerr << "Error : = expected >> " << nextToken_equal.getVal() << " << huh huh ??" << std::endl; //we got a var_name as expected before, now we check that the next token is an equel, we quit if else
                exit(EXIT_FAILURE);
            }

            Node_int_decl node_int = Node_int_decl();

            node_int.var_name = nextToken_var_name.getVal();

            if(doesVarAlreadyDeclared(node_int.var_name)){ //verify if var_name is already declared
                std::cerr << "Error : var_name already declared >> " << node_int.var_name << " << this already exist" << std::endl;
                exit(EXIT_FAILURE);
            } 

            node_int.expr = parse_expr(); //we try to parse an expression, the compiler will quit if it is not

            this->known_var.push_back(node_int.var_name); //if everything goes right, then we register the var_name in our vector of var_name

            Node_holder node_hold = Node_holder(nodes_type::int_decl);
            node_hold.int_decl = node_int;

            this->nodes.push_back(node_hold);

        }

    }

}

//Try to parse an expression from the current token

Node_expr Parser::parse_expr(){

    if(this->current_index + 1 > this->tokens.size()){
        std::cerr << "Error : parser out of range" << std::endl;
        exit(EXIT_FAILURE);
    }

    Node_expr res;
    res.node_type = nodes_type::expr;

    Token current_t = get_token();

    if(current_t.getType() == TokenType::int_literal){ //if next token is int_literal, we just use his value

        res.int_literal = current_t;

        if(res.int_literal.getType() == TokenType::null){
            std::cerr << "Error :: null token" << std::endl;
            exit(EXIT_FAILURE);
        }

    }else if(current_t.getType() == TokenType::var_name){ //if next token is a reference to a var_name we change is_var_ref so the generator can known it is supposed to be a reference
    
        if(doesVarAlreadyDeclared(current_t.getVal())){

            res.is_var_ref = true;
            Node_var_ref var_ref_set = Node_var_ref();
            var_ref_set.var_name = current_t.getVal();
            res.var_ref = var_ref_set;

        }else{ //if the var_name is not known from the parser, then we throw an error

            std::cerr << "Error : unknown var_name >> " << current_t.getVal() << " << unknown shit" << std::endl;
            exit(EXIT_FAILURE);

        }

    }else{

        std::cerr << "Error : invalid token >> " << current_t.getVal() << " << icant fr" << std::endl;
        exit(EXIT_FAILURE);
        
    }

    return res;

}

//Return the token at the current index and increment the index

Token Parser::get_token(){
    
    Token res = this->tokens.at(this->current_index);
    this->current_index++;
    return res;

}

//Return true if the current index is within the length of the vector of tokens

bool Parser::tokens_current_token_exist(){

    if(this->current_index < this->tokens.size()){
        return true;
    }else{
        return false;
    }

}

//Return the nodes knowns of the parser

std::vector<Node_holder>* Parser::get_nodes(){
    return &this->nodes;
}

//Return the vector of known var

std::vector<std::string>* Parser::get_known_var(){
    return &this->known_var;
}

bool Parser::doesVarAlreadyDeclared(std::string str){

    auto it = std::find(this->known_var.begin(), this->known_var.end(), str);

    if(it == this->known_var.end()){
        return false;
    }else{
        return true;
    }

}