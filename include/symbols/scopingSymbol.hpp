#ifndef __SCOPING_SYMBOL_HPP
#define __SCOPING_SYMBOL_HPP

#include "symbol.hpp"
#include "expressions/expression.hpp"
#include "variable.hpp"

namespace symbols{

class scopingSymbol : virtual public symbol
{
protected:
    /* data */
    std::list<std::shared_ptr<variable>> vars;
    std::string value;  //Should probably be changed later
    int stackOffset;
    void prologueCodeGen(std::ofstream&);
public:
    std::shared_ptr<variable> findVarByName(std::string);
    std::shared_ptr<variable> createVariable(std::string);
    void epilogueCodeGen(std::ofstream&);
    scopingSymbol(/* args */);
    ~scopingSymbol();
};

inline scopingSymbol::scopingSymbol(/* args */){stackOffset = -8;}
inline scopingSymbol::~scopingSymbol(){}


}

#endif