#include <symbols/statement.hpp>
#include <symbols/expressions/variable.hpp>

namespace symbols {

class variableDefinition : public statement
{
private:
    /* data */
    std::shared_ptr<variable> var;
    variableDefinition(/* args */);
public:
    virtual void print();
    virtual void codeGen(std::ofstream&);
    static std::shared_ptr<variableDefinition> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~variableDefinition();
};

variableDefinition::variableDefinition(/* args */){}
variableDefinition::~variableDefinition(){}

std::shared_ptr<variableDefinition> variableDefinition::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    std::shared_ptr<variableDefinition> var(new variableDefinition);
    token t;
    std::string name;
    t = popToken(it);
    if(t.type != INT_KEYWORD){
        std::cerr << "Statement: expected 'int' keyword\n";
        exit(1);
    }
    t = popToken(it);
    if(t.type != IDENTIFIER){
        var->print();
        std::cerr << "Statement: Expected identifier\n";
        exit(1);
    }
    name = t.token_string;
    // t = peekToken(it);
    // if(t.type == SEMICOLON){
    //     popToken(it);
    //     return var;
    // }
    // if(t.type != ASSIGNMENT){
    //     var->print();
    //     std::cerr << "Statement: missing semicolon\n";
    //     exit(1);
    // }
    // var->value = expression::parse(it, scope);
    t = popToken(it);
    if(t.type != SEMICOLON){
        var->print();
        std::cerr << "Statement: missing semicolon\n";
        exit(1);
    }
    var->var = scope->createVariable(name, NULL, scope);
    return var;
}

void variableDefinition::print(){
    // std::cout << "VAR: " << name;
    // if(value){
    //     std::cout << " ";
    //     value->print();
    // }
}

void variableDefinition::codeGen(std::ofstream& ofs){
    var->codeGen(ofs);
    ofs << "push\t%rax\n";
}


std::shared_ptr<statement> statement::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
    std::shared_ptr<statement> stmt(new statement);

    token t = peekToken(it);

    switch (t.type){
        case RETURN_KEYWORD: {
            popToken(it);
            stmt->value = t.token_string;
            stmt->children.push_back(expression::parse(it, scope));
            stmt->scope = scope;
            t = popToken(it);
            if(t.type != SEMICOLON){
                stmt->print();
                std::cerr << "Statement: missing semicolon\n";
                exit(1);
            }
            break;
        }
        case  INT_KEYWORD: {
            stmt = variableDefinition::parse(it, scope);
            break;
        }
        default: {
            stmt->children.push_back(expression::parse(it, scope));
            break;
        }
    }
    // if(t.type != RETURN_KEYWORD){
    //     std::cerr << "Statement: expected return keyword\n";
    //     exit(1); 
    // }
    return stmt;
}

void statement::print(){
    std::cout << "STATEMENT: " << value << "\n";

    for(symbol_ptr s : children){
        s->print();
    }
}

void statement::codeGen(std::ofstream& ofs){
    
    for(symbol_ptr s : children){
        s->codeGen(ofs);
    }
    scope->epilogueCodeGen(ofs);
}

}