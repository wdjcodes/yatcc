#ifndef __VARIABLEREFERENCE_HPP
#define __VARIABLEREFERENCE_HPP

#include "expression.hpp"
#include "../variable.hpp"

namespace symbols {

class variableReference : public expression
{
private:
    /* data */
    variableReference();
    std::shared_ptr<variable> var;
public:
    virtual void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    virtual void print();
    ~variableReference();
};

inline variableReference::variableReference(/* args */){}

inline variableReference::~variableReference()
{
}


}

#endif