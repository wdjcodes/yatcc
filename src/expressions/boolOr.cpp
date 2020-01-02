#include <symbols/expressions/boolOr.hpp>
#include <symbols/expressions/boolAnd.hpp>
#include <codegen.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> boolOrExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = boolAndExpression::parse(it);
    token tok = peekToken(it);
    while(tok.type == BOOL_OR){
        popToken(it);
        std::shared_ptr<expression> r = boolAndExpression::parse(it);
        l = std::make_shared<boolOrExpression>(l, r);
        tok = peekToken(it);
    }

    return l;
}

void boolOrExpression::codeGen(std::ofstream& ofs){
    std::string or_label = codegen::genLabel("_or");
    std::string end_label = codegen::genLabel("_end");
    left->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nje\t" << or_label << "\nmovl\t$1, %eax\njmp\t"
        << end_label << "\n" << or_label << ":\n";
    right->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nmovl\t$0, %eax\nsetne\t%al\n"<< end_label << ":\n";
}

}