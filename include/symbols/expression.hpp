#ifndef __EXPRESSION_HPP
#define __EXPRESSION_HPP

#include "symbol.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class expression : public virtual symbol
{
private:
    std::shared_ptr<expression> left;
    std::shared_ptr<expression> right;
    token op;
protected:
    /* data */
    expression(/* args */);
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    expression(token, std::shared_ptr<expression>, std::shared_ptr<expression>);
    ~expression();
};
inline expression::expression(/* args */)
{
    type = EXPRESSION;
}

inline expression::expression(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r){
    left = l;
    right = r;
    if(o.type != PLUS && o.type != MINUS){
        throw "Bad Expression operator";
    }
    op = o;
}

inline expression::~expression(){}

}




#endif