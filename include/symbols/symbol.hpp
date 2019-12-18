
#ifndef __SYMBOL_HPP
#define __SYMBOL_HPP

#include <list>
#include <iostream>
#include <fstream>

#include "../token.hpp"

namespace symbols {

using namespace tokens;

enum symbol_type {
    PROGRAM,
    FUNCTION,
    STATEMENT,
    EXPRESSION
};

class symbol
{
protected:
    /* data */
    symbol_type type;
    std::list<std::shared_ptr<symbol>> children;
    static token nextToken(std::list<token>::iterator&);
public:
    virtual void print();
    virtual void codeGen(std::ofstream&);
    symbol(/* args */);
    ~symbol();
};

symbol::symbol(/* args */)
{
}

symbol::~symbol()
{
}

token symbol::nextToken(std::list<token>::iterator& it){
    token t = *it;
    it++;
    return t;
}

void symbol::print(){}

void symbol::codeGen(std::ofstream& ofs){}


typedef std::shared_ptr<symbol> symbol_ptr;


template <class T>
class typedSymbol : public symbol
{
private:
    /* data */

protected:
    T value;
    typedSymbol(/* args */);

public:
    ~typedSymbol();
    // virtual symbol *parse(list<token>);
    template <class TT>
    friend std::ostream& operator<<(std::ostream& os, const typedSymbol<TT>& sym);
    template <class TT>
    friend std::ostream& operator<<(std::ostream& os, const typedSymbol<TT>* sym);
};

template <class T>
typedSymbol<T>::typedSymbol(){}

template <class T>
typedSymbol<T>::~typedSymbol(){}

template <class T>
std::ostream& operator<<(std::ostream& os, const typedSymbol<T>& sym){
    os << sym.type << ": " << sym.value;
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const typedSymbol<T>* sym){
    os << sym->type << ": " << sym->value;
    return os;
}

}

#endif