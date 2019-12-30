#include <symbols/symbol.hpp>
#include <symbols/expression.hpp>
#include <symbols/term.hpp>
#include <symbols/factor.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){
    
    std::shared_ptr<expression> e(new expression);
    e->pTerm = term::parse(it);

    return e;
}


void expression::codeGen(std::ofstream& ofs){
    pTerm->codeGen(ofs);
}

}