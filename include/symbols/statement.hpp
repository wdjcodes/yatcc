#ifndef __STATEMENT_HPP
#define __STATEMENT_HPP

#include "symbol.hpp"
#include "expression.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class statement : public typedSymbol<std::string>
{
private:
    /* data */
    statement(/* args */);
public:
    virtual void print();
    static std::shared_ptr<statement> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~statement();
};

statement::statement(/* args */)
{
    type = STATEMENT;
}

statement::~statement() {}

std::shared_ptr<statement> statement::parse(std::list<token>::iterator& it){
    std::shared_ptr<statement> stmt(new statement);

    token t = popToken(it);

    if(t.type != RETURN_KEYWORD){
        std::cerr << "Statement: expected return keyword\n";
        exit(1); 
    }
    stmt->value = t.token_string;

    stmt->children.push_back(expression::parse(it));

    t = popToken(it);
    if(t.type != SEMICOLON){
        std::cerr << "Statement: missing semicolon\n";
        exit(1);
    }
    return stmt;
}

void statement::print(){
    std::cout << "STATEMENT: " << value << "\n";

    for(symbol_ptr s : children){
        s->print();
    }
}

void statement::codeGen(std::ofstream& ofs){
    
    for(symbol_ptr s : children){
        s->codeGen(ofs);
    }
    ofs << "ret";
}



}

#endif