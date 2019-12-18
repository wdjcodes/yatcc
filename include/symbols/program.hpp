#ifndef __PROGRAM_HPP
#define __PROGRAM_HPP

#include <list>
#include <iostream>
#include <fstream>

#include "symbol.hpp"
#include "function.hpp"
#include "../token.hpp"

using namespace tokens;


namespace symbols{

class program : public typedSymbol<std::string>
{
private:
    /* data */
    program();
public:
    virtual void print();
    static program *parse(std::list<token>);
    void codeGen(std::string);
    // void codeGen(char *);
    ~program();
};

program::program()
{
    type = PROGRAM;
}

program *program::parse(std::list<token> tokens){

    program *prog = new program();
    std::list<token>::iterator it = tokens.begin();
    /* Do parsing */
    while(tokens.size() > 0){
        prog->children.push_back(function::parse(it));
        /*Remove list items from begin -> it*/
        while(tokens.begin() != it){
            tokens.pop_front();
        }
    }

    return prog;

}

void program::print(){
    std::cout << "PROGRAM:\n";
    for(symbol_ptr s : children){
        s->print();
    }
}

void program::codeGen(std::string of_name){
    std::ofstream ofs;
    ofs.open(of_name);

    for(symbol_ptr s : children){
        s->codeGen(ofs);
    }
}


}


#endif