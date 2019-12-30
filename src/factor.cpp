
#include <symbols/symbol.hpp>
#include <symbols/factor.hpp>
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
    std::cout << "factor: " << this->value << "\n";
}


class negationOperator : public factor
{
private:
    /* data */
    std::shared_ptr<factor> operand;
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
    std::shared_ptr<factor> operand;
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
    std::shared_ptr<factor> operand;
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




std::shared_ptr<factor> factor::parse(std::list<token>::iterator& it){

    std::shared_ptr<factor> fact;

    token t = nextToken(it);

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
            f->operand = factor::parse(it);
            fact = f;
            break;
        } 
        case TILDE: {
            std::shared_ptr<bitNotOperator> f(new bitNotOperator);
            f->operand = factor::parse(it);
            fact = f;
            break;
        }
        case EXCLAMATION_PT: {
            std::shared_ptr<boolNotOperator> f(new boolNotOperator);
            f->operand = factor::parse(it);
            fact = f;
            break;
        }
        default: {
            std::cerr << "factor: Not a valid factor\n";
            exit(1);
        }

    }

    return fact;
}


}
