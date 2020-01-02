#ifndef __ADDITIVE_EXP_HPP
#define __ADDITIVE_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {

class additiveExpression : public expression
{

protected:
    additiveExpression();

public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    additiveExpression(token, std::shared_ptr<expression>, std::shared_ptr<expression>);
    ~additiveExpression();
};
inline additiveExpression::additiveExpression(/* args */)
{
    type = EXPRESSION;
}

inline additiveExpression::additiveExpression(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r){
    left = l;
    right = r;
    if(o.type != PLUS && o.type != MINUS){
        throw "Bad Expression operator";
    }
    op = o.type;
}

inline additiveExpression::~additiveExpression(){}

}




#endif