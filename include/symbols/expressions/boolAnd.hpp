#ifndef __BOOLAND_EXP_HPP
#define __BOOLAND_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {


class boolAndExpression : public expression
{
private:
    /* data */
    boolAndExpression(/* args */);
public:
    boolAndExpression(std::shared_ptr<expression>, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~boolAndExpression();
};

inline boolAndExpression::boolAndExpression(/* args */)
{
}

inline boolAndExpression::boolAndExpression(std::shared_ptr<expression>l, std::shared_ptr<expression>r, std::shared_ptr<scopingSymbol> s){
    left = l;
    right = r;
    scope = s;
}

inline boolAndExpression::~boolAndExpression()
{
}

}

#endif