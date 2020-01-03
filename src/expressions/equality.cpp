#include <symbols/expressions/equality.hpp>
#include <symbols/expressions/additive.hpp>
#include <codegen.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> equalityExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = additiveExpression::parse(it);
    token tok = peekToken(it);
    while(tok.type == EQUAL || tok.type == NEQUAL){
        popToken(it);
        std::shared_ptr<expression> r = additiveExpression::parse(it);
        l = std::make_shared<equalityExpression>(tok, l, r);
        tok = peekToken(it);
    }

    return l;
}

void equalityExpression::codeGen(std::ofstream& ofs){
    left->codeGen(ofs);
    ofs << "push\t%rax\n";
    right->codeGen(ofs);
    ofs << "pop\t%rcx\ncmpl\t%eax,%ecx\nmovl\t$0,%eax\n";

    switch (op){
        case EQUAL: {
            ofs << "sete\t%al\n";
            break;
        }
        case NEQUAL: {
            ofs << "setne\t%al\n";
            break;
        }
        default:
            exit(1);
    }
}

}