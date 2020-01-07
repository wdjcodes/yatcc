#ifndef __IF_STATEMENT_HPP
#define __IF_STATEMENT_HPP

#include "statement.hpp"
#include "../expressions/expression.hpp"
namespace symbols {

class ifStatement : public statement
{
private:
    /* data */
    std::shared_ptr<expression> test;
    std::shared_ptr<statement> if_true;
    std::shared_ptr<statement> else_false;
    ifStatement(/* args */);
public:
    static std::shared_ptr<ifStatement> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    void print();
    ~ifStatement();
};

inline ifStatement::ifStatement(/* args */){else_false = NULL;}
inline ifStatement::~ifStatement(){}

}


#endif