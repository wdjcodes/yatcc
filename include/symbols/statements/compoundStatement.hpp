#ifndef __COMPOUND_STATEMENT_HPP
#define __COMPOUND_STATEMENT_HPP

#include "statement.hpp"
#include "../scopingSymbol.hpp"
namespace symbols {

class compoundStatement : public statement, public scopingSymbol
{
private:
    /* data */
    std::list<std::shared_ptr<blockItem>> statements;
    std::shared_ptr<variable> localStackBase;
    compoundStatement(std::shared_ptr<scopingSymbol>);
    void prologueCodeGen(std::ofstream&);
public:
    static std::shared_ptr<compoundStatement> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    void print();
    void epilogueCodeGen(std::ofstream&);
    ~compoundStatement();
};
inline compoundStatement::~compoundStatement(){}

}

#endif