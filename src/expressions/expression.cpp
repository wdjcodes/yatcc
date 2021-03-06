#include <symbols/symbol.hpp>
#include <symbols/expressions/expression.hpp>
#include <symbols/expressions/variableAssignment.hpp>
// #include <symbols/expressions/boolOr.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    //Just a dummy to call the lowest precedent expression parser first
    std::shared_ptr<expression> exp = variableAssignment::parse(it, scope);
    return exp;
}

const std::vector<token_type> validOps = {};

}