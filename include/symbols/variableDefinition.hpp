#ifndef __VARIABLE_DEFINITION_HPP
#define __VARIABLE_DEFINITION_HPP

#include "blockItem.hpp"
#include "expressions/expression.hpp"

namespace symbols {

class variableDefinition : public blockItem
{
private:
    /* data */
    std::shared_ptr<variable> var;
    std::shared_ptr<expression> initialValue;
    variableDefinition(/* args */);
public:
    virtual void print();
    virtual void codeGen(std::ofstream&);
    static std::shared_ptr<variableDefinition> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~variableDefinition();
};

inline variableDefinition::variableDefinition(/* args */){initialValue = NULL;}
inline variableDefinition::~variableDefinition(){}

}

#endif