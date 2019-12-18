#ifndef __FUNCTION_HPP
#define __FUNCTION_HPP

#include <list>
#include <iostream>
#include <fstream>


#include "symbol.hpp"
#include "statement.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class function : public typedSymbol<std::string>
{
private:
    /* data */
    function(); 
public:
    virtual void print();
    static std::shared_ptr<function> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~function();
};

function::function(/* args */)
{
    type = FUNCTION;
}

function::~function(){}

std::shared_ptr<function> function::parse(std::list<token>::iterator& it){

    std::shared_ptr<function> func(new function);

    token t = nextToken(it);
    if(t.type != INT_KEYWORD){
        std::cerr << "Function: expected int keyword\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != IDENTIFIER){
        std::cerr << "Function: expected identifier\n";
        exit(1);
    }
    func->value = t.token_string;
    t = nextToken(it);
    if(t.type != PARENTH_OPEN){
        std::cerr << "Function: expected '('\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != PARENTH_CLOSE){
        std::cerr << "Function: expected ')'\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != BRACE_OPEN){
        std::cerr << "Function: expected '{'\n";
        exit(1);
    }

    func->children.push_back(statement::parse(it));
    
    t = nextToken(it);
    if(t.type != BRACE_CLOSE){
        std::cerr << "Function: expected '}'\n";
        exit(1);
    }
    // func->children.push_back(expression::parse(it));
    return func;

}

void function::print(){
    std::cout << "FUNCTION: " << value << "\n";

    for(symbol_ptr s : children){
        s->print();
    }
}

void function::codeGen(std::ofstream& ofs){

    ofs << ".globl " << value << "\n" << value << ":\n";
    for(symbol_ptr s : children){
        ofs << "\t";
        s->codeGen(ofs);
    }

}


}


#endif