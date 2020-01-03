#include <symbols/expressions/equality.hpp>
#include <symbols/expressions/relational.hpp>

using namespace tokens;

namespace symbols {

const std::vector<token_type> equalityExpression::validOps = {EQUAL, NEQUAL};

std::shared_ptr<expression> equalityExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = relationalExpression::parse(it);
    token tok = peekToken(it);
    while(isValidOp(tok.type)){
        popToken(it);
        std::shared_ptr<expression> r = relationalExpression::parse(it);
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

bool equalityExpression::isValidOp(token_type t){
    return is_valid_op<equalityExpression>(t);
}

}