#ifndef NODES_DEF
#define NODES_DEF

#include "Token.hpp"

struct Node_expr;
struct Node_ret;
struct Node_int_decl;
struct Node_holder;
struct Node_var_ref;

enum class nodes_type{
    no_type,
    expr,
    ret,
    int_decl,
    var_ref,
    holder
};

struct Node{

    Node(){
        this->node_type = nodes_type::no_type;
    }

    nodes_type node_type;

};

struct Node_var_ref : Node{

    Node_var_ref(){
        this->node_type = nodes_type::var_ref;
    }

    std::string var_name;

};

struct Node_expr: Node{

    Node_expr(){
        this->node_type = nodes_type::expr;
        this->is_var_ref = false;
    }

    Token int_literal;
    Node_var_ref var_ref;
    bool is_var_ref;

};

struct Node_ret : Node{

    Node_ret(){
        this->node_type = nodes_type::ret;
    }

    Node_expr expr;

};

struct Node_int_decl : Node{

    Node_int_decl(){
        this->node_type = nodes_type::int_decl;
    }

    std::string var_name;
    Node_expr expr;

};

struct Node_holder : Node{

    Node_holder(nodes_type type_set){
        this->node_type = type_set;
    }

    Node_expr expr;
    Node_ret ret;
    Node_int_decl int_decl;
    Node_var_ref var_ref;
};

#endif