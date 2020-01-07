
#include <symbols/symbol.hpp>
#include <symbols/expressions/factor.hpp>
#include <symbols/expressions/variableReference.hpp>
#include <token.hpp>

using namespace tokens;

namespace symbols{

template <class T>
class typedFactor : public factor, public typedSymbol<T>
{
private:
    /* data */
public:
    typedFactor(/* args */);
    void codeGen(std::ofstream&);
    virtual void print();
    friend factor;
    ~typedFactor();
};

template <class T>
inline typedFactor<T>::typedFactor(/* args */){}
template <class T>
inline typedFactor<T>::~typedFactor(){}

typedef typedFactor<int> intFactor;

template<>
inline void intFactor::codeGen(std::ofstream& ofs){
    ofs << "movl\t$" << value << ", %eax\n";
}

template <class T>
inline void typedFactor<T>::print() {
    std::cout << this->value;
}


class negationOperator : public factor
{
private:
    /* data */
    // std::shared_ptr<factor> operand;
public:
    negationOperator(/* args */);
    ~negationOperator();
    friend factor;
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

class bitNotOperator : public factor
{
private:
    /* data */
    // std::shared_ptr<factor> operand;
public:
    bitNotOperator(/* args */);
    ~bitNotOperator();
    friend factor;
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

class boolNotOperator : public factor
{
private:
    /* data */
    // std::shared_ptr<factor> operand;
public:
    boolNotOperator(/* args */);
    ~boolNotOperator();
    friend factor;
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


class parenGroup : public factor
{
private:
    /* data */
    // std::shared_ptr<expression> exp;
public:
    parenGroup(/* args */);
    ~parenGroup();
    friend factor;
    virtual void codeGen(std::ofstream&);
    virtual void print();
};

parenGroup::parenGroup(/* args */)
{
}

parenGroup::~parenGroup()
{
}

void parenGroup::codeGen(std::ofstream& ofs){
    operand->codeGen(ofs);
}

void parenGroup::print(){
    std::cout << "(";
    operand->print();
    std::cout << ")";
}



std::shared_ptr<expression> factor::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){

    std::shared_ptr<factor> fact;

    token t = popToken(it);

    // if(t.type != INT_LITERAL){
        
    // }
    // exp->value = std::stoi(t.token_string);
    switch (t.type){
        case INT_LITERAL: {
            std::shared_ptr<intFactor> f(new intFactor);
            f->value = std::stoi(t.token_string);
            fact = f;
            break;
        }
        case MINUS: {
            std::shared_ptr<negationOperator> f(new negationOperator);
            f->operand = factor::parse(it, scope);
            fact = f;
            break;
        } 
        case TILDE: {
            std::shared_ptr<bitNotOperator> f(new bitNotOperator);
            f->operand = factor::parse(it, scope);
            fact = f;
            break;
        }
        case EXCLAMATION_PT: {
            std::shared_ptr<boolNotOperator> f(new boolNotOperator);
            f->operand = factor::parse(it, scope);
            fact = f;
            break;
        }
        case PARENTH_OPEN: {
            std::shared_ptr<parenGroup> f(new parenGroup);
            f->operand = expression::parse(it, scope);
            t = popToken(it);
            if(t.type != PARENTH_CLOSE){
                std::cerr << "Factor: Missing ')'\n";
                exit(1);
            }
            fact = f;
            break;
        }
        case IDENTIFIER: {
            it--;
            return variableReference::parse(it, scope);
            // std::shared_ptr<variable> f(new variable);
            // f->name = t.token_string;
            // f->scope = scope;
            break;
        }
        default: {
            std::cerr << "factor: Not a valid factor: " << t.token_string << "\n";
            exit(1);
        }

    }

    return fact;
}


}
