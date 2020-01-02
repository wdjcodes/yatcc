#include <symbols/symbol.hpp>
#include <symbols/term.hpp>
#include <symbols/factor.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> term::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> l = factor::parse(it);
    token tok = peekToken(it);
    while(tok.type == ASTERISK || tok.type == F_SLASH){
        popToken(it);
        std::shared_ptr<expression> r = factor::parse(it);
        // l = std::shared_ptr<expression>(expression(tok, l, r));
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
        case ASTERISK:{
            ofs << "imul\t%ecx, %eax\n";
            break;
        }
        case F_SLASH: {
            ofs << "cdq\nidiv\t%ecx\n";
            break;
        }
        default:{
            exit(1);
        }
    }
}

}