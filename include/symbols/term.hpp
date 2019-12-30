#ifndef __TERM_HPP
#define __TERM_HPP

#include "symbol.hpp"
#include "expression.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class term : public expression
// class term : public typedSymbol<int>
{
private:
    std::shared_ptr<term> pTerm;
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