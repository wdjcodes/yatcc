#include <symbols/statement.hpp>
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
    t = popToken(it);
    if(t.type != SEMICOLON){
        var->print();
        std::cerr << "Statement: missing semicolon\n";
        exit(1);
    }
    var->var = scope->createVariable(name);
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

class variableAssignment : public statement
{
private:
    /* data */
    std::shared_ptr<variable> var;
    std::shared_ptr<expression> value;
    variableAssignment(/* args */);
public:
    // virtual void print();
    virtual void codeGen(std::ofstream&);
    variableAssignment(std::string, std::shared_ptr<expression>, std::shared_ptr<scopingSymbol>);
    // static std::shared_ptr<variableAssignment> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    ~variableAssignment();
};

variableAssignment::variableAssignment(/* args */){}
variableAssignment::variableAssignment(std::string name, std::shared_ptr<expression> val, std::shared_ptr<scopingSymbol>s){
    var = s->findVarByName(name);
    if(!var){
        std::cerr << "Var: " << name << " is underfined\n";
        exit(1);
    }
    value = val;
    scope = s;
}
variableAssignment::~variableAssignment(){}

void variableAssignment::codeGen(std::ofstream& ofs){
    value->codeGen(ofs);
    ofs << "mov\t%rax, " << var->getStackBaseOffset() << "(%rbp)\n";
}

// std::shared_ptr<variableAssignment> variableAssignment::parse(std::list<token>::iterator& it, std::shared_ptr<scopingSymbol> scope){
//     std::shared_ptr<variableAssignment> var(new variableAssignment);
//     token t;
//     std::string name;
//     t = popToken(it);
//     if(t.type != IDENTIFIER){
//         var->print();
//         std::cerr << "Statement: Expected identifier\n";
//         exit(1);
//     }
//     name = t.token_string;
//     t = peekToken(it);
//     if(t.type == SEMICOLON){
//         popToken(it);
//         return var;
//     }
//     if(t.type != ASSIGNMENT){
//         var->print();
//         std::cerr << "Statement: missing semicolon\n";
//         exit(1);
//     }
//     t = popToken(it);
//     var->initialValue = expression::parse(it, scope);
//     if(t.type != SEMICOLON){
//         var->print();
//         std::cerr << "Statement: missing semicolon\n";
//         exit(1);
//     }
//     var->var = scope->createVariable(name, NULL, scope);
//     return var;
// }



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
        case IDENTIFIER: {
            t = popToken(it);
            std::string name = t.token_string;
            t = peekToken(it);
            if(t.type == ASSIGNMENT){
                //Variable assignment
                popToken(it);
                std::shared_ptr<expression> value = expression::parse(it, scope);
                t = popToken(it);
                if(t.type != SEMICOLON){
                    std::cerr << "Statement: missing semicolon\n";
                    exit(1);
                }
                std::shared_ptr<variableAssignment> va(new variableAssignment(name, value, scope));
                return va;
            }
            //might be a variable only expression we'll pass it on to the default expression parser
            //need to rewind iterator one step first
            it--;
            stmt->children.push_back(expression::parse(it, scope));
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