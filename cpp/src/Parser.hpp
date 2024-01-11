#ifndef PARSER_DEF
#define PARSER_DEF

#include <algorithm>
#include "Nodes.hpp"
#include <vector>
#include "Token.hpp"
#include <string>
#include <sstream>
#include <iostream>

class Parser{

    public:

        Parser(std::vector<Token>& tokens_set);
        void parse();
        std::vector<Node_holder>* get_nodes();
        std::vector<std::string>* get_known_var();


    private:

        std::vector<Token> tokens;
        std::vector<Node_holder> nodes;
        Node_expr parse_expr();
        int current_index;
        Token get_token();
        bool tokens_current_token_exist();
        std::vector<std::string> known_var;
        bool doesVarAlreadyDeclared(std::string);

};



#endif