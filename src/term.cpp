#include <symbols/symbol.hpp>
#include <symbols/term.hpp>
#include <symbols/factor.hpp>

using namespace tokens;

namespace symbols {

std::shared_ptr<term> term::parse(std::list<token>::iterator& it){

    std::shared_ptr<term> t(new term);

    t->pFactor = factor::parse(it);

    return t;
}

void term::codeGen(std::ofstream& ofs){
    pFactor->codeGen(ofs);
}

}