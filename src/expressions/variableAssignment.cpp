#include <symbols/expressions/variableAssignment.hpp>
#include <symbols/expressions/boolOr.hpp>


namespace symbols{

std::shared_ptr<expression> variableAssignment::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    token t = popToken(it);
    std::shared_ptr<variableAssignment> var(new variableAssignment);
    if(t.type != IDENTIFIER || peekToken(it).type != ASSIGNMENT){
        //Not a variable assignment go down the parse chain
        it--;
        return boolOrExpression::parse(it, scope);
    }
    var->var = scope->findVarByName(t.token_string);
    if(!var->var){
        std::cerr << t.token_string << "is undefined\n";
        exit(1);
    }
    var->scope = scope;
    t = popToken(it);
    if(t.type != ASSIGNMENT){
        std::cerr << "Expected an assigner token\n";
        exit(1);
    }
    var->value = expression::parse(it, scope);
    return var;
}

void variableAssignment::codeGen(std::ofstream& ofs){
    value->codeGen(ofs);
    ofs << "mov\t%rax, " << var->getStackBaseOffset() << "(%rbp)\n";
}

void variableAssignment::print(){
    var->print();
    std::cout << " = ";
    value->print();
    std::cout << "\n";
}

}