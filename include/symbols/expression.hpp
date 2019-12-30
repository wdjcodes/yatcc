#ifndef __EXPRESSION_HPP
#define __EXPRESSION_HPP

#include "symbol.hpp"
#include "term.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class expression : public virtual symbol
{
private:
    std::shared_ptr<term> pTerm;
protected:
    /* data */
    expression(/* args */);
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~expression();
};
inline expression::expression(/* args */)
{
    type = EXPRESSION;
}

inline expression::~expression(){}

}

#endif