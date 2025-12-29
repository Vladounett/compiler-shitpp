#include "Parser.hpp"
#include <variant>

Parser::Parser(std::vector<Token> tokens_set){
    this->tokens = tokens_set;
    this->currentTokenIndex = 0;
    this->returnFlag = false;
}

void Parser::parse(){
    while(!check(TokenType::eof)){
        NodeStatementHandle nsh = parseStatement();
        if(nsh){
            this->parsedProgram.push_back(std::move(nsh));
        }else{
            std::cerr << "Error : parseStatement got nullptr" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    if(!returnFlag){
        std::cerr << "Error : don't you want to leave at some point ?" << std::endl;
        exit(EXIT_FAILURE);
    }
}

NodeStatementHandle Parser::parseStatement(){

    if(checkSequence({"i", "declare"})){
        advance();
        advance();
        return parseIntDecl();
    }else if(checkSequence({"i", "am", "leaving"})){
        advance();
        advance();
        advance();
        return parseReturn();
    }else if(checkSequence({"hello"})){
        advance();
        consume(TokenType::line_ender, "Error : line_ender expected");
        return std::make_unique<NodeStatement>(NodeProgStart{});
    }else if(checkSequence({"goodbye"})){
        advance();
        consume(TokenType::line_ender, "Error : line_ender expected");
        return std::make_unique<NodeStatement>(NodeProgEnd{});
    }

    std::cerr << "Error : expected statement" << std::endl;
    exit(EXIT_FAILURE);
    return nullptr;
}

NodeStatementHandle Parser::parseReturn(){
    NodeExprHandle expr = parseExpr();
    consume(TokenType::line_ender, "Error : line_ender expected");
    if(expr){
        this->returnFlag = true;
        return std::make_unique<NodeStatement>(NodeReturn{std::move(expr)});
    }else{
        return nullptr;
    }
}

NodeStatementHandle Parser::parseIntDecl(){
    Token var_name = consume(TokenType::identifier, "Error : identifier expected");
    consume(TokenType::equal, "Error : equal expected");
    NodeExprHandle expr = parseExpr();
    consume(TokenType::line_ender, "Error : line_ender expected");

    this->known_var.push_back(var_name.getVal());

    if(expr){
        return std::make_unique<NodeStatement>(NodeIntDecl{var_name.getVal(), std::move(expr)});
    }else{
        return nullptr;
    }
}

NodeExprHandle Parser::parseExpr(){
    if(check(TokenType::int_literal)){
        return std::make_unique<NodeExpr>(NodeIntLiteral{stoi(this->consume(TokenType::int_literal, "Error : int_literal expected").getVal())});
    }else if(check(TokenType::identifier)){
        if(this->isVarAlreadyDeclared(this->peek().getVal())){
            return std::make_unique<NodeExpr>(NodeVarRef{this->consume(TokenType::identifier, "Error : identifier expected").getVal()});
        }else{
            std::cerr << "Error : unknown var_name : " << this->peek().getVal() << std::endl;
            exit(EXIT_FAILURE);
            return nullptr;
        }
    }
    return nullptr;
}

Token& Parser::peek() {
    return tokens[currentTokenIndex];
}

Token& Parser::lookAhead(short offset){
    if(currentTokenIndex + offset >= this->tokens.size()){
        return tokens.back();
    }else{
        return tokens[currentTokenIndex + offset];
    }
}

Token& Parser::advance() {
    if(currentTokenIndex + 1 < this->tokens.size()) currentTokenIndex++; 
    return tokens[currentTokenIndex-1];
}

Token& Parser::consume(TokenType type, std::string errMsg) {
    if(this->check(type)){
        return advance();
    }
    std::cerr << errMsg << std::endl;
    exit(EXIT_FAILURE);
}

bool Parser::isVarAlreadyDeclared(std::string str){
    auto it = std::find(this->known_var.begin(), this->known_var.end(), str);
    if(it == this->known_var.end()){
        return false;
    }else{
        return true;
    }
}

bool Parser::check(TokenType type){
    return this->peek().getType() == type;
}

bool Parser::check(TokenType type, std::string str){
    return this->peek().getType() == type && peek().getVal() == str;
}

bool Parser::checkSequence(std::initializer_list<std::string> seq) {
    size_t i = 0;
    for (const auto& s : seq) {
        if (this->lookAhead(i).getVal() != s) {
            return false;
        }
        ++i;
    }
    return true;
}

void Parser::debugParsedProgram(){
    for(NodeStatementHandle &nsh : this->parsedProgram){
        debugStatement(*nsh);
    }
}

void Parser::debugStatement(NodeStatement &ns){
    std::visit(overload{
        [this](NodeReturn& ret) {std::cout << "Return : "; debugExpr(*ret.val); std::cout << std::endl;},
        [this](NodeIntDecl& decl) {std::cout << "IntDecl : "; debugExpr(*decl.val); std::cout << std::endl;},
        [](NodeProgStart&) {std::cout << "ProgStart" << std::endl;},
        [](NodeProgEnd&) {std::cout << "ProgEnd" << std::endl;}
    }, ns);
}

void Parser::debugExpr(NodeExpr &ndh){
    std::visit(overload{
        [](NodeIntLiteral& intLit) {std::cout << "IntLiteral(" << intLit.val << ")";},
        [](NodeVarRef& varRef) {std::cout << "VarRef(" + varRef.var_name + ")";}
    }, ndh);
}

std::vector<NodeStatementHandle>& Parser::getParsedProgram(){
    return this->parsedProgram;
}