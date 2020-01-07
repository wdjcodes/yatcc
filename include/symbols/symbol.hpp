
#ifndef __SYMBOL_HPP
#define __SYMBOL_HPP

#include <list>
#include <iostream>
#include <fstream>

#include "../token.hpp"

using namespace tokens;

namespace symbols {

class scopingSymbol;

enum symbol_type {
    PROGRAM,
    FUNCTION,
    STATEMENT,
    EXPRESSION,
    TERM,
    FACTOR
};

class symbol
{
protected:
    /* data */
    symbol_type type;
    std::list<std::shared_ptr<symbol>> children;
    static token popToken(std::list<token>::iterator&);
    static token peekToken(std::list<token>::iterator&);
    std::shared_ptr<scopingSymbol> scope;
public:
    virtual void print();
    virtual void codeGen(std::ofstream&);
    symbol(/* args */);
    ~symbol();
};

inline symbol::symbol(/* args */)
{
}

inline symbol::~symbol()
{
}

inline token symbol::popToken(std::list<token>::iterator& it){
    token t = *it;
    it++;
    return t;
}

inline token symbol::peekToken(std::list<token>::iterator& it){
    return *it;
}

inline void symbol::print(){}

inline void symbol::codeGen(std::ofstream& ofs){}


typedef std::shared_ptr<symbol> symbol_ptr;


template <class T>
class typedSymbol : public virtual symbol
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
inline typedSymbol<T>::typedSymbol(){}

template <class T>
inline typedSymbol<T>::~typedSymbol(){}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const typedSymbol<T>& sym){
    os << sym.type << ": " << sym.value;
    return os;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const typedSymbol<T>* sym){
    os << sym->type << ": " << sym->value;
    return os;
}

}

#endif