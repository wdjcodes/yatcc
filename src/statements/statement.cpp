#include <symbols/statements/statement.hpp>
#include <symbols/expressions/expression.hpp>
#include <symbols/statements/returnStatement.hpp>
#include <symbols/statements/ifStatement.hpp>
#include <symbols/variable.hpp>

namespace symbols {

std::shared_ptr<statement> statement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    std::shared_ptr<statement> stmt;

    token t = peekToken(it);

    switch (t.type){
        case RETURN_KEYWORD: {
            stmt = returnStatement::parse(it, scope);
            // popToken(it);
            // stmt->value = t.token_string;
            // stmt->children.push_back(expression::parse(it, scope));
            // stmt->scope = scope;
            break;
        }
        // case  INT_KEYWORD: {
        //     stmt = variableDefinition::parse(it, scope);
        //     break;
        // }
        case IF_KEYWORD: {
            //If's should not have semicolon go ahead and return
            return ifStatement::parse(it, scope);
        }
        default: {
            stmt = expression::parse(it, scope);
            break;
        }
    }
    t = popToken(it);
    if(t.type != SEMICOLON){
        stmt->print();
        std::cerr << "Statement: missing semicolon\n";
        exit(1);
    }
    return stmt;
}

void statement::print(){
    // std::cout << "STATEMENT: " << value << "\n";

    for(symbol_ptr s : children){
        s->print();
    }
}

void statement::codeGen(std::ofstream& ofs){
    
    for(symbol_ptr s : children){
        s->codeGen(ofs);
    }
    // scope->epilogueCodeGen(ofs);
}

}