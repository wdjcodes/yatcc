#ifndef __EXPRESSSION_HPP
#define __EXPRESSION_HPP

#include "symbols.hpp"
#include "../token.hpp"

using namespace tokens;

namespace symbols {

class expression : public typedSymbol<int>
{
private:
    /* data */
    expression(/* args */);
public:
    virtual void print();
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    void codeGen(std::ofstream&);
    ~expression();
};

expression::expression(/* args */)
{
    type = EXPRESSION;
}

expression::~expression(){}

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> exp(new expression);

    token t = nextToken(it);

    if(t.type != INT_LITERAL){
        std::cerr << "Expression: expected an int\n";
        exit(1);
    }
    exp->value = std::stoi(t.token_string);

    return exp;
}

void expression::print() {
    std::cout << "EXPRESSION: " << value << "\n";
}

void expression::codeGen(std::ofstream& ofs){
    ofs << "$" << value;
}


}


#endif