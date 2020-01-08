#include <symbols/symbol.hpp>
#include <symbols/scopingSymbol.hpp>

namespace symbols {

symbol::symbol(/* args */) :
    scopeLevel(typeid(scopingSymbol)),
    symbolReturns(false)
{
    scope = NULL;
    // symbolReturns = false;
}

symbol::symbol(const std::type_info& t):
    scopeLevel(t),
    symbolReturns(false)
{
    scope = NULL;
    // symbolReturns = false;
}

void symbol::assignScope(std::shared_ptr<scopingSymbol> s){
    if(scopeLevel == typeid(scopingSymbol)){
        scope = s;
        return;
    }
    std::shared_ptr<scopingSymbol> currentScope = s;
    while(currentScope && typeid(*currentScope) != scopeLevel){
        currentScope = currentScope->getParentScope();
    }
    if(!currentScope){
        std::cerr << "This type of statement must be used within a " << scopeLevel.name() << "\n";
        exit(1);
    }
    scope = currentScope;
}


}