
#include <symbols/symbol.hpp>
#include <symbols/expression.hpp>
#include <token.hpp>

using namespace tokens;

namespace symbols{

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


}
