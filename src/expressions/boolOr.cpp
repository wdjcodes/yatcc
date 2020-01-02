#include <symbols/expressions/boolOr.hpp>
#include <symbols/expressions/additive.hpp>
#include <codegen.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> boolOrExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = additiveExpression::parse(it);
    token tok = peekToken(it);
    while(tok.type == BOOL_OR){
        popToken(it);
        std::shared_ptr<expression> r = additiveExpression::parse(it);
        l = std::make_shared<boolOrExpression>(l, r);
        tok = peekToken(it);
    }

    return l;
}

void boolOrExpression::codeGen(std::ofstream& ofs){
    std::string clause_label = codegen::genLabel("_caluse");
    std::string end_label = codegen::genLabel("_end");
    left->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nje\t" << clause_label << "\nmovl\t$1, %eax\njmp\t"
        << end_label << "\n" << clause_label << ":\n";
    right->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nmovl\t$0, %eax\nsetne\t%al\n"<< end_label << ":\n";
}

}