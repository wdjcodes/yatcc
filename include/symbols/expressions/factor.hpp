#ifndef __FACTOR_HPP
#define __FACTOR_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {

class factor : public expression
{
protected:
    /* data */
    factor(/* args */);
    std::shared_ptr<expression> operand;
public:
    // static std::shared_ptr<factor> parse(std::list<token>::iterator&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~factor();
};
inline factor::factor(/* args */)
{
    type = FACTOR;
}

inline factor::~factor(){}

}

#endif