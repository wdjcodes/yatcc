
#include <symbols/symbol.hpp>
#include <symbols/expression.hpp>
#include <token.hpp>

using namespace tokens;

namespace symbols{

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> exp;

    token t = nextToken(it);

    // if(t.type != INT_LITERAL){
        
    // }
    // exp->value = std::stoi(t.token_string);
    switch (t.type){
        case INT_LITERAL: {
            std::shared_ptr<intExpression> iExp(new intExpression);
            iExp->value = std::stoi(t.token_string);
            exp = iExp;
            break;
        }
        default: {
            std::cerr << "Expression: Not a valid expression\n";
            exit(1);
        }

    }

    return exp;
}


}
