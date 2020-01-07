#ifndef __STATEMENT_HPP
#define __STATEMENT_HPP

// #include "symbol.hpp"
// #include "../scopingSymbol.hpp"
#include "../blockItem.hpp"
// #include "../token.hpp"

using namespace tokens;

namespace symbols {

class statement : public blockItem
{
private:
    /* data */
protected:
    statement(/* args */);
    std::shared_ptr<scopingSymbol> scope;
public:
    virtual void print();
    static std::shared_ptr<statement> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    ~statement();
};

inline statement::statement(/* args */)
{
    type = STATEMENT;
}

inline statement::~statement() {}

}

#endif