#ifndef IR_NODES
#define IR_NODES
#include <vector>
#include <string>

struct IRNode;

using IRProgram = std::vector<IRNode>;

enum class IRop{
    LoadConst,
    LoadVar,
    StoreVar,
    Return
};

struct IRNode{
    IRop op;
    int var_dst = -1;
    int var_src = -1;
    int immediate_val = 0;
    std::string var;
};

#endif