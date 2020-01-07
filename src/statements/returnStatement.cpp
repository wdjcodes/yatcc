#include <symbols/statements/returnStatement.hpp>

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
    std::cout << "\n";
}

std::shared_ptr<returnStatement> returnStatement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    token t = popToken(it);
    std::shared_ptr<returnStatement>s(new returnStatement);
    s->scope = scope;
    if(t.type != RETURN_KEYWORD){
        std::cerr << "Expected Return Keyword\n";
        exit(1);
    }

    s->value = expression::parse(it, scope);
    return s;

}

}