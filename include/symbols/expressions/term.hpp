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
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    static bool isValidOp(token_type);
    void codeGen(std::ofstream&);
    void print();
    term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r, std::shared_ptr<scopingSymbol> s);
    ~term();
    friend expression;
};
inline term::term(/* args */)
{
    type = TERM;
}

inline term::term(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r, std::shared_ptr<scopingSymbol> s){
    type = TERM;
    left = l;
    right = r;
    scope = s;
    if(!isValidOp(o.type)){
        throw "Bad Term operation\n";
    }
    op = o.type;
}

inline term::~term(){}

}

#endif