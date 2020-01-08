#include <symbols/blockItem.hpp>
#include <symbols/variableDefinition.hpp>

namespace symbols {

std::shared_ptr<blockItem> blockItem::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){

    token t = peekToken(it);
    switch(t.type){
        case INT_KEYWORD: {
            return variableDefinition::parse(it, scope);
        }
        default: {
            return statement::parse(it, scope);
        }
    }

}

}