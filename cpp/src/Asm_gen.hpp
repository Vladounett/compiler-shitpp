#ifndef GEN_DEF
#define GEN_DEF

#include "Nodes.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Asm_gen{

    public:

        Asm_gen(std::vector<Node_holder> nodes_set, std::vector<std::string> known_var_set);
        std::string build_asm();


    private:

        std::vector<Node_holder> nodes;
        std::vector<std::string> known_var;
        std::string gen_node(Node_ret n);
        std::string gen_node(Node_int_decl n);

};



#endif