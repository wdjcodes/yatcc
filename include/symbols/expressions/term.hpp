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
    // // std::shared_ptr<term> pTerm;
    // std::shared_ptr<term> left;
    // std::shared_ptr<term> right;
    // token_type op;
protected:
    /* data */
    term(/* args */);
public:
    // static std::shared_ptr<term> parse(std::list<token>::iterator&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r);
    ~term();
};
inline term::term(/* args */)
{
    type = TERM;
}

inline term::term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r){
    type = TERM;
    left = l;
    right = r;
    if(o.type != MULTIPLY && o.type != DIVIDE){
        throw "Bad Term operation\n";
    }
    op = o.type;
}

inline term::~term(){}

}

#endif