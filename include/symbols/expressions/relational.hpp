#ifndef __RELATIONAL_EXP_HPP
#define __RELATIONAL_EXP_HPP

#include "expression.hpp"
#include "../../token.hpp"

using namespace tokens;

namespace symbols {


class relationalExpression : public expression
{
private:
    /* data */
    relationalExpression(/* args */);
    static const std::vector<token_type> validOps;
public:
    relationalExpression(token, std::shared_ptr<expression>, std::shared_ptr<expression>);
    static bool isValidOp(token_type);
    void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~relationalExpression();
    friend expression;
};

inline relationalExpression::relationalExpression(/* args */){}

inline relationalExpression::relationalExpression(token o, std::shared_ptr<expression>l, std::shared_ptr<expression>r){
    left = l;
    right = r;
    if(!isValidOp(o.type)){
        std::cerr << "Bad Equality Operation\n";
        exit(1);
    }
    op = o.type;
}

inline relationalExpression::~relationalExpression()
{
}

}

#endif