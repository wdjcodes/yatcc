#ifndef __FACTOR_HPP
#define __FACTOR_HPP

#include "symbol.hpp"
#include "term.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class factor : public virtual term
{
protected:
    /* data */
    factor(/* args */);
public:
    static std::shared_ptr<factor> parse(std::list<token>::iterator&);
    ~factor();
};
inline factor::factor(/* args */)
{
    type = FACTOR;
}

inline factor::~factor(){}

}

#endif