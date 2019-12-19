#ifndef __EXPRESSION_HPP
#define __EXPRESSION_HPP

#include "symbol.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class expression : public virtual symbol
// class expression : public typedSymbol<int>
{
protected:
    /* data */
    expression(/* args */);
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~expression();
};
inline expression::expression(/* args */)
{
    type = EXPRESSION;
}

inline expression::~expression(){}

template <class T>
class typedExpression : public expression, public typedSymbol<T>
{
private:
    /* data */
    typedExpression(/* args */);
public:
    void codeGen(std::ofstream&);
    virtual void print();
    friend expression;
    ~typedExpression();
};

template <class T>
inline typedExpression<T>::typedExpression(/* args */){}
template <class T>
inline typedExpression<T>::~typedExpression(){}

typedef typedExpression<int> intExpression;

template<>
inline void intExpression::codeGen(std::ofstream& ofs){
    ofs << "$" << value;
}

template <class T>
inline void typedExpression<T>::print() {
    std::cout << "EXPRESSION: " << this->value << "\n";
}


}

#endif