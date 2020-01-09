#include <symbols/expressions/boolAnd.hpp>
#include <symbols/expressions/equality.hpp>
#include <codegen.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> boolAndExpression::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    
    std::shared_ptr<expression> l = equalityExpression::parse(it, scope);
    token tok = peekToken(it);
    while(tok.type == BOOL_AND){
        popToken(it);
        std::shared_ptr<expression> r = equalityExpression::parse(it, scope);
        l = std::make_shared<boolAndExpression>(l, r, scope);
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

void boolAndExpression::print(){
    left->print();
    std::cout << " && ";
    right->print();
}

}