#ifndef __SCOPING_SYMBOL_HPP
#define __SCOPING_SYMBOL_HPP

#include "symbol.hpp"
// #include "expressions/expression.hpp"
#include "variable.hpp"

namespace symbols{

class scopingSymbol : virtual public symbol
{
protected:
    /* data */
    std::list<std::shared_ptr<variable>> vars;
    std::string value;  //Should probably be changed later
    void prologueCodeGen(std::ofstream&);
    bool reachesEnd;
    int stackOffset;
public:
    std::shared_ptr<variable> findVarByName(std::string);
    std::shared_ptr<variable> findLocalVarByName(std::string);
    std::shared_ptr<variable> createVariable(std::string);
    std::shared_ptr<scopingSymbol> getParentScope();
    int getStackOffset();
    virtual void epilogueCodeGen(std::ofstream&);
    scopingSymbol(/* args */);
    ~scopingSymbol();
};

inline scopingSymbol::scopingSymbol(/* args */){stackOffset = -8; reachesEnd = true;}
inline scopingSymbol::~scopingSymbol(){}
inline int scopingSymbol::getStackOffset(){return stackOffset;}
inline std::shared_ptr<scopingSymbol> scopingSymbol::getParentScope(){return scope;}


}

#endif