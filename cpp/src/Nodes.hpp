#ifndef NODES_DEF
#define NODES_DEF

#include "Token.hpp"

struct Node_expr;
struct Node_ret;

enum class nodes_type{
    no_type,
    expr,
    ret,
    holder
};

struct Node{

    Node(){
        this->node_type = nodes_type::no_type;
    }

    nodes_type node_type;

};


struct Node_expr: Node{

    Node_expr(){
        this->node_type = nodes_type::expr;
    }

    Token int_literal;

};

struct Node_ret : Node{

    Node_ret(){
        this->node_type = nodes_type::ret;
    }

    Node_expr expr;

};

struct Node_holder : Node{

    Node_holder(nodes_type type_set){
        this->node_type = type_set;
    }

    Token int_literal;
    Node_expr expr;
    Node_ret ret;
};

#endif