
#include <symbols/symbol.hpp>
#include <symbols/expression.hpp>
#include <token.hpp>

using namespace tokens;

namespace symbols{

template <class T>
class typedExpression : public expression, public typedSymbol<T>
{
private:
    /* data */
public:
    typedExpression(/* args */);
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
    ofs << "movl\t$" << value << ", %eax\n";
}

template <class T>
inline void typedExpression<T>::print() {
    std::cout << "EXPRESSION: " << this->value << "\n";
}


class negationOperator : public expression
{
private:
    /* data */
    std::shared_ptr<expression> operand;
public:
    negationOperator(/* args */);
    ~negationOperator();
    friend expression;
    virtual void codeGen(std::ofstream&);
    virtual void print();
};

negationOperator::negationOperator(/* args */){}
negationOperator::~negationOperator(){}

void negationOperator::print(){
    std::cout << "-( ";
    operand->print();
    std::cout << ")";
}

void negationOperator::codeGen(std::ofstream& ofs){
    operand->codeGen(ofs);
    ofs << "neg\t%eax\n";
}

class bitNotOperator : public expression
{
private:
    /* data */
    std::shared_ptr<expression> operand;
public:
    bitNotOperator(/* args */);
    ~bitNotOperator();
    friend expression;
    virtual void codeGen(std::ofstream&);
    virtual void print();
};

bitNotOperator::bitNotOperator(/* args */){}
bitNotOperator::~bitNotOperator(){}

void bitNotOperator::print(){
    std::cout << "~( ";
    operand->print();
    std::cout << ")";
}

void bitNotOperator::codeGen(std::ofstream& ofs){
    operand->codeGen(ofs);
    ofs << "not\t%eax\n";
}

class boolNotOperator : public expression
{
private:
    /* data */
    std::shared_ptr<expression> operand;
public:
    boolNotOperator(/* args */);
    ~boolNotOperator();
    friend expression;
    virtual void codeGen(std::ofstream&);
    virtual void print();
};

boolNotOperator::boolNotOperator(/* args */){}
boolNotOperator::~boolNotOperator(){}

void boolNotOperator::print(){
    std::cout << "!( ";
    operand->print();
    std::cout << ")";
}

void boolNotOperator::codeGen(std::ofstream& ofs){
    operand->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nmovl\t$0,%eax\nsete\t%al\n";
}




std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> exp;

    token t = nextToken(it);

    // if(t.type != INT_LITERAL){
        
    // }
    // exp->value = std::stoi(t.token_string);
    switch (t.type){
        case INT_LITERAL: {
            std::shared_ptr<intExpression> e(new intExpression);
            e->value = std::stoi(t.token_string);
            exp = e;
            break;
        }
        case MINUS: {
            std::shared_ptr<negationOperator> e(new negationOperator);
            e->operand = expression::parse(it);
            exp = e;
            break;
        } 
        case TILDE: {
            std::shared_ptr<bitNotOperator> e(new bitNotOperator);
            e->operand = expression::parse(it);
            exp = e;
            break;
        }
        case EXCLAMATION_PT: {
            std::shared_ptr<boolNotOperator> e(new boolNotOperator);
            e->operand = expression::parse(it);
            exp = e;
            break;
        }
        default: {
            std::cerr << "Expression: Not a valid expression\n";
            exit(1);
        }

    }

    return exp;
}


}
