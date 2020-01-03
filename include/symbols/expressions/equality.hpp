#ifndef __EQUALITY_EXP_HPP
#define __EQUALITY_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {


class equalityExpression : public expression
{
private:
    /* data */
    equalityExpression(/* args */);
    static const std::vector<token_type> validOps;
public:
    equalityExpression(token, std::shared_ptr<expression>, std::shared_ptr<expression>);
    void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    static bool isValidOp(token_type);
    ~equalityExpression();
    friend expression;
};

inline equalityExpression::equalityExpression(/* args */)
{
}

inline equalityExpression::equalityExpression(token o, std::shared_ptr<expression>l, std::shared_ptr<expression>r){
    left = l;
    right = r;
    if(!isValidOp(o.type)){
        std::cerr << "Bad Equality Operation\n";
        exit(1);
    }
    op = o.type;
}

inline equalityExpression::~equalityExpression()
{
}

}

#endif