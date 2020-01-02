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
    boolOrExpression(std::shared_ptr<expression>, std::shared_ptr<expression>);
    void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~boolOrExpression();
};

inline boolOrExpression::boolOrExpression(/* args */)
{
}

inline boolOrExpression::boolOrExpression(std::shared_ptr<expression>l, std::shared_ptr<expression>r){
    left = l;
    right = r;
}

inline boolOrExpression::~boolOrExpression()
{
}

}

#endif