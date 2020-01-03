#ifndef __BOOLOR_EXP_HPP
#define __BOOLOR_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {


class boolOrExpression : public expression
{
private:
    /* data */
    boolOrExpression(/* args */);
public:
    boolOrExpression(std::shared_ptr<expression>, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~boolOrExpression();
};

inline boolOrExpression::boolOrExpression(/* args */)
{
}

inline boolOrExpression::boolOrExpression(std::shared_ptr<expression>l, std::shared_ptr<expression>r, std::shared_ptr<scopingSymbol> s){
    left = l;
    right = r;
    scope = s;
}

inline boolOrExpression::~boolOrExpression()
{
}

}

#endif