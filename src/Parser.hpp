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

        Parser(std::vector<Token> tokens_set);

        void parse();
        void debugParsedProgram();

        std::vector<NodeStatementHandle>& getParsedProgram();

    private:

        NodeStatementHandle parseStatement();
        NodeStatementHandle parseReturn();
        NodeStatementHandle parseIntDecl();

        NodeExprHandle parseExpr();

        std::vector<NodeStatementHandle> parsedProgram;
        std::vector<std::string> known_var;
        std::vector<Token> tokens;

        short currentLine;
        short currentTokenIndex;

        Token& peek();
        Token& advance();
        Token& consume(TokenType type, std::string errMsg);
        Token& lookAhead(short offset);

        bool isVarAlreadyDeclared(std::string);
        bool check(TokenType type);
        bool check(TokenType type, std::string str);
        bool checkSequence(std::initializer_list<std::string> seq);
        bool returnFlag;
        bool helloFlag;
        bool goodbyeFlag;

        void debugStatement(NodeStatement &nsh);
        void debugExpr(NodeExpr &ndh);
        void throwError(std::string);
};



#endif