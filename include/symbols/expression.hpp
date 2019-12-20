#ifndef __EXPRESSION_HPP
#define __EXPRESSION_HPP

#include "symbol.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class expression : public virtual symbol
// class expression : public typedSymbol<int>
{
protected:
    /* data */
    expression(/* args */);
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~expression();
};
inline expression::expression(/* args */)
{
    type = EXPRESSION;
}

inline expression::~expression(){}

}

#endif