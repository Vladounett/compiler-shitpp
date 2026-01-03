#ifndef NODES_DEF
#define NODES_DEF

#include "Token.hpp"
#include <optional>
#include <variant>
#include <memory>

struct NodeReturn;
struct NodeIntDecl;
struct NodeProgStart;
struct NodeProgEnd;

struct NodeVarRef;
struct NodeIntLiteral;

//Expressions

using NodeExpr = std::variant<NodeIntLiteral, NodeVarRef>;
using NodeExprHandle = std::unique_ptr<NodeExpr>;

//Statements

using NodeStatement = std::variant<NodeReturn, NodeIntDecl, NodeProgStart, NodeProgEnd>;
using NodeStatementHandle = std::unique_ptr<NodeStatement>;

/* -------------------------------------------------------------------- */

struct NodeVarRef {
    std::string var_name;
};

struct NodeIntLiteral {
    int val;
};

struct NodeReturn {
    NodeExprHandle val;
};

struct NodeProgStart{

};

struct NodeProgEnd{

};

struct NodeIntDecl {
    std::string var_name;
    NodeExprHandle val;
};

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

struct VarInfo{
    int offset;
};

#endif