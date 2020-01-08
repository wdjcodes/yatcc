#include <symbols/expressions/conditionalExpression.hpp>
#include <symbols/expressions/boolOr.hpp>
#include <codegen.hpp>

namespace symbols {

std::shared_ptr<expression> conditionalExpression::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){

    std::shared_ptr<expression> test = boolOrExpression::parse(it, scope);
    token t = peekToken(it);
    if(t.type != QUESTION){
        return test;
    }
    popToken(it);
    std::shared_ptr<conditionalExpression> e(new conditionalExpression);
    e->test = test;
    e->scope = scope;
    e->if_true = expression::parse(it, scope);
    
    t = popToken(it);
    if(t.type != COLON){
        std::cerr << "missing ':'\n";
        exit(1);
    }
    e->else_false = conditionalExpression::parse(it, scope);

    return e;
}

void conditionalExpression::print(){
    test->print();
    std::cout << " ? ";
    if_true->print();
    std::cout << " : ";
    else_false->print();
}


void conditionalExpression::codeGen(std::ofstream& ofs){
    std::string else_label = codegen::genLabel("_else");
    std::string skip_else_label = codegen::genLabel("_skip_else");
    test->codeGen(ofs);
    ofs << "cmpl\t$0,%eax\nje\t" << else_label << "\n";
    if_true->codeGen(ofs);
    ofs << "jmp\t" << skip_else_label << "\n" << else_label << ":\n";
    else_false->codeGen(ofs);
    ofs << skip_else_label << ":\n";
}


}