#include <symbols/statements/returnStatement.hpp>
#include <symbols/function.hpp>

namespace symbols {

void returnStatement::codeGen(std::ofstream& ofs){
    if(value){
        value->codeGen(ofs);
    }
    scope->epilogueCodeGen(ofs);
}

void returnStatement::print(){
    std::cout << "RETURN: ";
    if(value){
        value->print();
    }
}

std::shared_ptr<returnStatement> returnStatement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    token t = popToken(it);
    std::shared_ptr<returnStatement>s(new returnStatement);
    if(t.type != RETURN_KEYWORD){
        std::cerr << "Expected Return Keyword\n";
        exit(1);
    }

    s->value = expression::parse(it, scope);
    s->assignScope(scope);
    return s;

}

returnStatement::returnStatement(/* args */) :
    symbol(typeid(function))
{
    value = NULL;
    symbolReturns = true;
}

}