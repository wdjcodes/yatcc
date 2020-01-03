#ifndef __TERM_HPP
#define __TERM_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {

class term : public expression
// class term : public typedSymbol<int>
{
private:
    static const std::vector<token_type> validOps;
protected:
    /* data */
    term(/* args */);
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    static bool isValidOp(token_type);
    void codeGen(std::ofstream&);
    term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r);
    ~term();
    friend expression;
};
inline term::term(/* args */)
{
    type = TERM;
}

inline term::term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r){
    type = TERM;
    left = l;
    right = r;
    if(!isValidOp(o.type)){
        throw "Bad Term operation\n";
    }
    op = o.type;
}

inline term::~term(){}

}

#endif