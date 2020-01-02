#include <symbols/expressions/boolAnd.hpp>
#include <symbols/expressions/additive.hpp>
#include <codegen.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> boolAndExpression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> l = additiveExpression::parse(it);
    token tok = peekToken(it);
    while(tok.type == BOOL_AND){
        popToken(it);
        std::shared_ptr<expression> r = additiveExpression::parse(it);
        l = std::make_shared<boolAndExpression>(l, r);
        tok = peekToken(it);
    }

    return l;
}

void boolAndExpression::codeGen(std::ofstream& ofs){
    std::string and_label = codegen::genLabel("_and");
    std::string end_label = codegen::genLabel("_end");
    left->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\njne\t" << and_label << "\nmovl\t$0, %eax\njmp\t"
        << end_label << "\n" << and_label << ":\n";
    right->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nmovl\t$0, %eax\nsetne\t%al\n"<< end_label << ":\n";
}

}