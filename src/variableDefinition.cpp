#include <symbols/variableDefinition.hpp>

namespace symbols {

std::shared_ptr<variableDefinition> variableDefinition::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    std::shared_ptr<variableDefinition> var(new variableDefinition);
    // std::cout << "variableDefinition::parse<debug>: " << var->symbolReturns << var->causesReturn() << "\n";
    token t;
    std::string name;
    t = popToken(it);
    if(t.type != INT_KEYWORD){
        std::cerr << "Statement: expected 'int' keyword\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != IDENTIFIER){
        var->print();
        std::cerr << "Statement: Expected identifier\n";
        exit(1);
    }
    name = t.token_string;
    t = peekToken(it);
    if(t.type == ASSIGNMENT){
        popToken(it);
        var->initialValue = expression::parse(it, scope);
    }
    t = popToken(it);
    if(t.type != SEMICOLON){
        std::cerr << "Missing ';'\n";
        exit(1);
    }
    var->var = scope->createVariable(name);
    return var;
}

void variableDefinition::print(){
    std::cout << "VAR(";
    var->print();
    std::cout << ")";
    if(initialValue){
        std::cout << " = ";
        initialValue->print();
    }
}

void variableDefinition::codeGen(std::ofstream& ofs){
    if(initialValue){
        //variable has been initialized;
        initialValue->codeGen(ofs);
    } else {
        //Initialize variable to zero
        ofs << "mov\t$0, %rax\n";
    }
    // var->codeGen(ofs);
    ofs << "push\t%rax\n";
}


}