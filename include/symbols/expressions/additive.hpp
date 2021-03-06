#ifndef __ADDITIVE_EXP_HPP
#define __ADDITIVE_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {

class additiveExpression : public expression
{
private:
    static const std::vector<token_type> validOps;
protected:
    additiveExpression();

public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    static bool isValidOp(token_type);
    void codeGen(std::ofstream&);
    void print();
    additiveExpression(token, std::shared_ptr<expression>, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
    ~additiveExpression();
    friend expression;
};
inline additiveExpression::additiveExpression(/* args */)
{
    type = EXPRESSION;
}

inline additiveExpression::additiveExpression(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r, std::shared_ptr<scopingSymbol> s){
    left = l;
    right = r;
    scope = s;
    if(!isValidOp(o.type)){
        throw "Bad Expression operator";
    }
    op = o.type;
}

inline additiveExpression::~additiveExpression(){}

}




#endif