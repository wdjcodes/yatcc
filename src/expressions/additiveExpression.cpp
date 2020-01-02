#include <symbols/symbol.hpp>
#include <symbols/expressions/additive.hpp>
#include <symbols/expressions/term.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> additiveExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = term::parse(it);
    token tok = peekToken(it);
    while(tok.type == MINUS || tok.type == PLUS){
        popToken(it);
        std::shared_ptr<expression> r = term::parse(it);
        l = std::make_shared<additiveExpression>(tok, l, r);
        tok = peekToken(it);
    }

    return l;
}


void additiveExpression::codeGen(std::ofstream& ofs){
    // Process right operand first so that
    // ordering is correct for subtraction
    right->codeGen(ofs);
    ofs << "push\t%rax\n";
    left->codeGen(ofs);
    ofs << "pop\t%rcx\n";
    switch(op){
        case PLUS:{
            ofs << "addl\t%ecx, %eax\n";
            break;
        }
        case MINUS:{
            ofs << "subl\t%ecx, %eax\n";
            break;
        }
        default:{
            std::cerr << "Invalid op: Expected PLUS or MINUS\n";
            exit(1);
        }
    }
}

}