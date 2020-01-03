#include <symbols/expressions/relational.hpp>
#include <symbols/expressions/additive.hpp>

using namespace tokens;

namespace symbols {

const std::vector<token_type> relationalExpression::validOps = {LESS_THAN, GRATER_THAN, LESS_THAN_OR_EQUAL, GREATE_THAN_OR_EQUAL};


std::shared_ptr<expression> relationalExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = additiveExpression::parse(it);
    token tok = peekToken(it);
    while(isvalidOp(tok.type)){
        popToken(it);
        std::shared_ptr<expression> r = additiveExpression::parse(it);
        l = std::make_shared<relationalExpression>(tok, l, r);
        tok = peekToken(it);
    }

    return l;
}

void relationalExpression::codeGen(std::ofstream& ofs){
    left->codeGen(ofs);
    ofs << "push\t%rax\n";
    right->codeGen(ofs);
    ofs << "pop\t%rcx\ncmpl\t%eax,%ecx\nmovl\t$0,%eax\n";

    switch (op){
        case LESS_THAN: {
            ofs << "setl\t%al\n";
            break;
        }
        case GRATER_THAN: {
            ofs << "setg\t%al\n";
            break;
        }
        case LESS_THAN_OR_EQUAL: {
            ofs << "setle\t%al\n";
            break;
        }
        case GREATE_THAN_OR_EQUAL: {
            ofs << "setge\t%al\n";
            break;
        }
        default:
            exit(1);
    }
}

bool relationalExpression::isvalidOp(token_type t){
    return std::find(validOps.begin(), validOps.end(), t) != validOps.end();
}


}