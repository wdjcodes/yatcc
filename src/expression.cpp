#include <symbols/symbol.hpp>
#include <symbols/expression.hpp>
#include <symbols/term.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = term::parse(it);
    token tok = peekToken(it);
    while(tok.type == MINUS || tok.type == PLUS){
        popToken(it);
        std::shared_ptr<term> r = term::parse(it);
        // l = std::shared_ptr<expression>(expression(tok, l, r));
        l = std::make_shared<expression>(tok, l, r);
        tok = peekToken(it);
    }

    return l;
}


void expression::codeGen(std::ofstream& ofs){
    left->codeGen(ofs);
    ofs << "push\t%rax\n";
    right->codeGen(ofs);
    ofs << "pop\t%rcx\n";
    ofs << "addl\t%ecx, %eax\n";
}

}