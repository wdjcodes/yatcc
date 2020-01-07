#include <symbols/statement.hpp>
#include <symbols/expressions/expression.hpp>
#include <symbols/returnStatement.hpp>
#include <symbols/variable.hpp>

namespace symbols {

class variableDefinition : public statement
{
private:
    /* data */
    std::shared_ptr<variable> var;
    std::shared_ptr<expression> initialValue;
    variableDefinition(/* args */);
public:
    virtual void print();
    virtual void codeGen(std::ofstream&);
    static std::shared_ptr<variableDefinition> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~variableDefinition();
};

variableDefinition::variableDefinition(/* args */){initialValue = NULL;}
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
    t = peekToken(it);
    if(t.type == ASSIGNMENT){
        popToken(it);
        var->initialValue = expression::parse(it, scope);
    }
    var->var = scope->createVariable(name);
    return var;
}

void variableDefinition::print(){
    std::cout << "VAR(";
    var->print();
    std::cout << ")";
    if(initialValue){
        std::cout << " = ";
        initialValue->print();
    }
}

void variableDefinition::codeGen(std::ofstream& ofs){
    if(initialValue){
        //variable has been initialized;
        initialValue->codeGen(ofs);
    } else {
        //Initialize variable to zero
        ofs << "mov\t$0, %rax\n";
    }
    // var->codeGen(ofs);
    ofs << "push\t%rax\n";
}

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
        case  INT_KEYWORD: {
            stmt = variableDefinition::parse(it, scope);
            break;
        }
        // case IDENTIFIER: {
        //     t = popToken(it);
        //     std::string name = t.token_string;
        //     t = peekToken(it);
        //     it--;
        //     if(t.type == ASSIGNMENT){
        //         //Variable assignment
        //         // std::shared_ptr<expression> value = expression::parse(it, scope);
        //         // stmt = std::make_shared<variableAssignment>(name, value, scope);
        //         stmt = variableAssignment::parse(it, scope);
        //         break;
        //     }
        //     //might be an unused expression rewind it and pass on to expression parser
        //     it--;
        //     stmt = expression::parse(it, scope);
        //     // stmt->children.push_back(expression::parse(it, scope));
        //     break;

        // }
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