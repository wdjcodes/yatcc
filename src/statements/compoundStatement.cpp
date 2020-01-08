#include <symbols/statements/compoundStatement.hpp>

namespace symbols {

std::shared_ptr<compoundStatement> compoundStatement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){

    token t = popToken(it);
    if(t.type != BRACE_OPEN){
        std::cerr << "Internal compiler Error: compoundStatement Parser called without: '{'\n";
        exit(1);
    }
    std::shared_ptr<compoundStatement> compound_stmt(new compoundStatement(scope));
    t = peekToken(it);
    std::cout << "compoundStatement::parse<debug>: true " << true << " false " << false << "\n";
    while(t.type != BRACE_CLOSE){
        if(!compound_stmt->reachesEnd){
            popToken(it);
            t = peekToken(it);
            continue;
        }
        compound_stmt->statements.push_back(blockItem::parse(it, compound_stmt));
        compound_stmt->statements.back()->print();
        compound_stmt->symbolReturns = compound_stmt->statements.back()->causesReturn();
        compound_stmt->reachesEnd = !(compound_stmt->symbolReturns);
        t = peekToken(it);
    }
    t = popToken(it);
    if(t.type != BRACE_CLOSE){
        std::cerr << "expected '}'\n";
        exit(1);
    }

    return compound_stmt;

}

void compoundStatement::codeGen(std::ofstream& ofs){
    prologueCodeGen(ofs);
    for(auto s : statements){
        s->codeGen(ofs);
    }
    if(reachesEnd){
        epilogueCodeGen(ofs);
    }

}

void compoundStatement::print(){
    std::cout << "{\n";
    for(auto s : statements){
        s->print();
        std::cout << "\n";
    }
    std::cout << "} ";
}

void compoundStatement::prologueCodeGen(std::ofstream& ofs){
    ofs << "push\t%rsp\n";
}

void compoundStatement::epilogueCodeGen(std::ofstream& ofs){
    ofs << "mov\t" << localStackBase->getStackBaseOffset() << "(%rbp), %rsp\n";
}

compoundStatement::compoundStatement(std::shared_ptr<scopingSymbol> s){
    assignScope(s);
    stackOffset = s->getStackOffset();
    localStackBase = createVariable(".localStackBase");
}


}