#include <symbols/symbol.hpp>
#include <symbols/expressions/term.hpp>
#include <symbols/expressions/factor.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> term::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> l = factor::parse(it);
    token tok = peekToken(it);
    while(tok.type == MULTIPLY || tok.type == DIVIDE){
        popToken(it);
        std::shared_ptr<expression> r = factor::parse(it);
        l = std::make_shared<term>(tok, l, r);
        tok = peekToken(it);
    }

    return l;
}

void term::codeGen(std::ofstream& ofs){
    right->codeGen(ofs);
    ofs << "push\t%rax\n";
    left->codeGen(ofs);
    ofs << "pop\t%rcx\n";

    switch(op){
        case MULTIPLY:{
            ofs << "imul\t%ecx, %eax\n";
            break;
        }
        case DIVIDE: {
            ofs << "cdq\nidiv\t%ecx\n";
            break;
        }
        default:{
            exit(1);
        }
    }
}

}