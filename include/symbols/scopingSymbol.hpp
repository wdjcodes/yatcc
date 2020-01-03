#ifndef __SCOPING_SYMBOL_HPP
#define __SCOPING_SYMBOL_HPP

#include "symbol.hpp"
#include "variable.hpp"
#include "expressions/expression.hpp"

namespace symbols{

class scopingSymbol : virtual public symbol
{
protected:
    /* data */
    std::list<std::shared_ptr<variable>> vars;
    std::string value;  //Should probably be changed later
    int stackOffset;
public:
    std::shared_ptr<variable> findVarByName(std::string);
    // std::shared_ptr<variable> createVariable(std::string, std::shared_ptr<expression>);
    scopingSymbol(/* args */);
    ~scopingSymbol();
};

inline scopingSymbol::scopingSymbol(/* args */){stackOffset = -4;}
inline scopingSymbol::~scopingSymbol(){}


}

#endif