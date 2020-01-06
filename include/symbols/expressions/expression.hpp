#ifndef __EXPRESSION_HPP
#define __EXPRESSION_HPP

#include "../symbol.hpp"
#include "../../token.hpp"
#include "../scopingSymbol.hpp"

using namespace tokens;

namespace symbols {

class scopingSymbol;

class expression : public virtual symbol
{
private:
    static const std::vector<token_type> validOps;
protected:
    /* data */
    expression(/* args */);
    std::shared_ptr<expression> left;
    std::shared_ptr<expression> right;
    token_type op;
    template<class T>
    static bool is_valid_op(token_type);
    std::shared_ptr<scopingSymbol> scope;
public:
    static std::shared_ptr<expression> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    void codeGen(std::ofstream&);
    expression(token, std::shared_ptr<expression>, std::shared_ptr<expression>);
    ~expression();
};
inline expression::expression(/* args */)
{
    type = EXPRESSION;
}

inline expression::expression(token o, std::shared_ptr<expression> l, std::shared_ptr<expression> r){
    left = l;
    right = r;
    if(o.type != PLUS && o.type != MINUS){
        throw "Bad Expression operator";
    }
    op = o.type;
}

inline expression::~expression(){}

template<class T>
inline bool expression::is_valid_op(token_type t){
    return std::find(T::validOps.begin(), T::validOps.end(), t) != T::validOps.end();
}

}




#endif