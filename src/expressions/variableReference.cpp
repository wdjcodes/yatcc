#include <symbols/expressions/variableReference.hpp>

namespace symbols {

void variableReference::print(){
    var->print();
}

void variableReference::codeGen(std::ofstream& ofs){
    ofs << "mov\t" << var->getStackBaseOffset() << "(%rbp), %rax\n";
}

std::shared_ptr<expression> variableReference::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    token t = popToken(it);
    std::shared_ptr<variableReference> ref(new variableReference);
    if(t.type != IDENTIFIER){
        std::cerr << "Expected identifier\n";
        exit(1);
    }
    ref->var = scope->findVarByName(t.token_string);
    if(!ref->var){
        std::cerr << "Variable: " << t.token_string << "is undefined\n";
    }
    return ref;
}


}