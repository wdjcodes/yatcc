#ifndef __FUNCTION_HPP
#define __FUNCTION_HPP

#include <list>
#include <iostream>
#include <fstream>


#include "scopingSymbol.hpp"
#include "statement.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class function : public scopingSymbol
{
private:
    /* data */
    function();
    bool returnMissing;
public:
    virtual void print();
    static std::shared_ptr<function> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~function();
};

inline function::function(/* args */)
{
    type = FUNCTION;
    returnMissing = true;
}

inline function::~function(){}

}


#endif