#ifndef __RETURN_STATEMENT_HPP
#define __RETURN_STATEMENT_HPP

#include "statement.hpp"
#include "../expressions/expression.hpp"
#include "../function.hpp"

namespace symbols {

class returnStatement : public statement
{
private:
    /* data */
    returnStatement(/* args */);
    std::shared_ptr<expression> value;
public:
    static std::shared_ptr<returnStatement> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    static std::shared_ptr<returnStatement> returnZero();
    void codeGen(std::ofstream&);
    void print();
    ~returnStatement();
};
inline returnStatement::~returnStatement(){}



}

#endif