#ifndef __VARIABLE_ASSIGNMENT_HPP
#define __VARIABLE_ASSIGNMENT_HPP

#include "expression.hpp"

namespace symbols {

class variableAssignment : public expression
{
private:
    /* data */
    std::shared_ptr<variable> var;
    std::shared_ptr<expression> value;
    variableAssignment(/* args */);
    variableAssignment(std::string, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
public:
    // virtual void print();
    virtual void codeGen(std::ofstream&);
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    // static std::shared_ptr<variableAssignment> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~variableAssignment();
};

inline variableAssignment::variableAssignment(/* args */){}
inline variableAssignment::variableAssignment(std::string name, std::shared_ptr<expression> val, std::shared_ptr<scopingSymbol>s){
    var = s->findVarByName(name);
    if(!var){
        std::cerr << "Var: " << name << " is underfined\n";
        exit(1);
    }
    value = val;
    scope = s;
}

inline variableAssignment::~variableAssignment(){}


}

#endif