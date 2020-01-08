#ifndef __CONDITIONAL_EXPRESSION_HPP
#define __CONDITIONAL_EXPRESSION_HPP

#include "expression.hpp"

namespace symbols {

class conditionalExpression : public expression
{
private:
    /* data */
    std::shared_ptr<expression> test;
    std::shared_ptr<expression> if_true;
    std::shared_ptr<expression> else_false;
    conditionalExpression(/* args */);
public:
    virtual void codeGen(std::ofstream&);
    virtual void print();
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~conditionalExpression();
};

inline conditionalExpression::conditionalExpression(/* args */){}
inline conditionalExpression::~conditionalExpression(){}

}

#endif