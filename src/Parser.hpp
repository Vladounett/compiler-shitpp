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
        short current_line;
        short current_token;
        Token get_token();
        Token lastToken;
        bool tokens_current_token_exist();
        std::vector<std::string> known_var;
        bool doesVarAlreadyDeclared(std::string);
        void print_at();

};



#endif