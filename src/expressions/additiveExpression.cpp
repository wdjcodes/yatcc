#include <symbols/symbol.hpp>
#include <symbols/expressions/additive.hpp>
#include <symbols/expressions/term.hpp>

using namespace tokens;

namespace symbols {

const std::vector<token_type> additiveExpression::validOps = {PLUS, MINUS};

std::shared_ptr<expression> additiveExpression::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    
    std::shared_ptr<expression> l = term::parse(it, scope);
    token tok = peekToken(it);
    while(tok.type == MINUS || tok.type == PLUS){
        popToken(it);
        std::shared_ptr<expression> r = term::parse(it, scope);
        l = std::make_shared<additiveExpression>(tok, l, r, scope);
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

bool additiveExpression::isValidOp(token_type t){
    return is_valid_op<additiveExpression>(t);
}

void additiveExpression::print(){
    left->print();
    op == PLUS ? std::cout << " + " : std::cout << " - ";
    right->print();
}

}