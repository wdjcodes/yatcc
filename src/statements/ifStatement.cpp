#include <symbols/statements/ifStatement.hpp>
#include <codegen.hpp>

namespace symbols {

std::shared_ptr<ifStatement> ifStatement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    std::shared_ptr<ifStatement> stmt(new ifStatement);
    token t = popToken(it);
    if(t.type != IF_KEYWORD){
        std::cerr << "Expected 'if'\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != PARENTH_OPEN){
        std::cerr << "Missing '('\n";
        exit(1);
    }
    stmt->scope = scope;
    stmt->test = expression::parse(it, scope);
    t = popToken(it);
    if(t.type != PARENTH_CLOSE){
        std::cerr << "Missing ')'\n";
        exit(1);
    }
    stmt->if_true = statement::parse(it, scope);
    t = peekToken(it);
    if(t.type == ELSE_KEYWORD){
        popToken(it);
        stmt->else_false = statement::parse(it, scope);
    }
    return stmt;
}

void ifStatement::codeGen(std::ofstream& ofs){
    std::string else_label = codegen::genLabel("_else");
    std::string skip_else_label = codegen::genLabel("_skip_else");
    test->codeGen(ofs);
    ofs << "cmpl\t$0, %eax\nje\t" << else_label << "\n";
    if_true->codeGen(ofs);
    if(else_false){
        ofs << "jmp\t" << skip_else_label << "\n";
    }
    ofs << else_label <<":\n";
    if(else_false){
        else_false->codeGen(ofs);
        ofs << skip_else_label <<":\n";
    }
}

void ifStatement::print(){
    std::cout << "IF(";
    test->print();
    std::cout << "){\n";
    if_true->print();
    std::cout << "}\n";
    if(else_false){
        std::cout << "ELSE{";
        else_false->print();
        std::cout << "}\n";
    }
}


}