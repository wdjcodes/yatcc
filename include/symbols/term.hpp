#ifndef __TERM_HPP
#define __TERM_HPP

#include "symbol.hpp"
#include "factor.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class term : public symbol
// class term : public typedSymbol<int>
{
private:
    std::shared_ptr<factor> pFactor;
protected:
    /* data */
    term(/* args */);
public:
    static std::shared_ptr<term> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~term();
};
inline term::term(/* args */)
{
    type = TERM;
}

inline term::~term(){}

}

#endif