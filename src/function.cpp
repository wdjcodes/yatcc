#include <symbols/function.hpp>

namespace symbols{

std::shared_ptr<function> function::parse(std::list<token>::iterator& it){

    std::shared_ptr<function> func(new function);

    token t = popToken(it);
    if(t.type != INT_KEYWORD){
        std::cerr << "Function: expected int keyword\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != IDENTIFIER){
        std::cerr << "Function: expected identifier\n";
        exit(1);
    }
    func->value = t.token_string;
    t = popToken(it);
    if(t.type != PARENTH_OPEN){
        std::cerr << "Function: expected '('\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != PARENTH_CLOSE){
        std::cerr << "Function: expected ')'\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != BRACE_OPEN){
        std::cerr << "Function: expected '{'\n";
        exit(1);
    }

    t = peekToken(it);
    while(t.type != BRACE_CLOSE){
        func->children.push_back(statement::parse(it, func));
        t = peekToken(it);
    }
    
    t = popToken(it);
    if(t.type != BRACE_CLOSE){
        std::cerr << "Function: expected '}'\n";
        exit(1);
    }
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
    prologueCodeGen(ofs);
    for(symbol_ptr s : children){
        s->codeGen(ofs);
    }

}

}