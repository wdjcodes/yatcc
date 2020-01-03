#ifndef __VARIABLE_HPP
#define __VARIABLE_HPP

#include "expressions/expression.hpp"

namespace symbols {

class variable : public expression
{
private:
    /* data */
    std::string name;
    std::shared_ptr<expression> value;
    int offset;
public:
    virtual void codeGen(std::ofstream&);
    virtual void print();
    friend bool operator==(std::shared_ptr<variable>, std::string);
    variable(std::string, int, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
    ~variable();
};

// inline variable::variable(/* args */){}

inline variable::variable(std::string n, int o, std::shared_ptr<expression> v, std::shared_ptr<scopingSymbol> s){
    name = n;
    offset = o;
    value = v;
    scope = s;
}

inline variable::~variable()
{
}

inline bool operator==(std::shared_ptr<variable>v, std::string s){
    return !v->name.compare(s);
}


}

#endif