
#ifndef __SYMBOL_HPP
#define __SYMBOL_HPP

namespace symbols {

#include <list>
#include <iostream>

#include "token.hpp"

using namespace tokens;


enum symbol_type {
    PROGRAM,
    FUNCTION,
    STATEMENT,
    EXPRESSION
};

class symbol
{
protected:
    /* data */
    symbol_type type;
    std::list<std::shared_ptr<symbol>> children;
    static token nextToken(std::list<token>::iterator&);
public:
    virtual void print();
    symbol(/* args */);
    ~symbol();
};

symbol::symbol(/* args */)
{
}

symbol::~symbol()
{
}

token symbol::nextToken(std::list<token>::iterator& it){
    token t = *it;
    it++;
    return t;
}

void symbol::print(){}

template <class T>
class typedSymbol : public symbol
{
private:
    /* data */

protected:
    T value;
    typedSymbol(/* args */);

public:
    ~typedSymbol();
    // virtual symbol *parse(list<token>);
    template <class TT>
    friend std::ostream& operator<<(std::ostream& os, const typedSymbol<TT>& sym);
    template <class TT>
    friend std::ostream& operator<<(std::ostream& os, const typedSymbol<TT>* sym);
};

template <class T>
typedSymbol<T>::typedSymbol(){}

template <class T>
typedSymbol<T>::~typedSymbol(){}

template <class T>
std::ostream& operator<<(std::ostream& os, const typedSymbol<T>& sym){
    os << sym.type << ": " << sym.value;
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const typedSymbol<T>* sym){
    os << sym->type << ": " << sym->value;
    return os;
}

class expression : public typedSymbol<std::string>
{
private:
    /* data */
    expression(/* args */);
public:
    virtual void print();
    static std::shared_ptr<expression> parse(std::list<token>::iterator&);
    ~expression();
};

expression::expression(/* args */)
{
    type = EXPRESSION;
}

expression::~expression(){}

std::shared_ptr<expression> expression::parse(std::list<token>::iterator& it){

    std::shared_ptr<expression> exp(new expression);

    token t = nextToken(it);

    if(t.type != INT_LITERAL){
        std::cerr << "Expression: expected an int\n";
        exit(1);
    }
    exp->value = t.token_string;

    return exp;
}

void expression::print() {
    std::cout << "EXPRESSION: " << value << "\n";
}

class statement : public typedSymbol<std::string>
{
private:
    /* data */
    statement(/* args */);
public:
    virtual void print();
    static std::shared_ptr<statement> parse(std::list<token>::iterator&);
    ~statement();
};

statement::statement(/* args */)
{
    type = STATEMENT;
}

statement::~statement() {}

std::shared_ptr<statement> statement::parse(std::list<token>::iterator& it){
    std::shared_ptr<statement> stmt(new statement);

    token t = nextToken(it);

    if(t.type != RETURN_KEYWORD){
        std::cerr << "Statement: expected return keyword\n";
        exit(1); 
    }
    stmt->value = t.token_string;

    stmt->children.push_back(expression::parse(it));

    t = nextToken(it);
    if(t.type != SEMICOLON){
        std::cerr << "Statement: missing semicolon\n";
        exit(1);
    }
    return stmt;
}

void statement::print(){
    std::cout << "STATEMENT: " << value << "\n";

    for(std::shared_ptr<symbol> s : children){
        s->print();
    }
}


class function : public typedSymbol<std::string>
{
private:
    /* data */
    function(); 
public:
    virtual void print();
    static std::shared_ptr<function> parse(std::list<token>::iterator&);
    ~function();
};

function::function(/* args */)
{
    type = FUNCTION;
}

function::~function(){}

std::shared_ptr<function> function::parse(std::list<token>::iterator& it){

    std::shared_ptr<function> func(new function);

    token t = nextToken(it);
    if(t.type != INT_KEYWORD){
        std::cerr << "Function: expected int keyword\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != IDENTIFIER){
        std::cerr << "Function: expected identifier\n";
        exit(1);
    }
    func->value = t.token_string;
    t = nextToken(it);
    if(t.type != PARENTH_OPEN){
        std::cerr << "Function: expected '('\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != PARENTH_CLOSE){
        std::cerr << "Function: expected ')'\n";
        exit(1);
    }
    t = nextToken(it);
    if(t.type != BRACE_OPEN){
        std::cerr << "Function: expected '{'\n";
        exit(1);
    }

    func->children.push_back(statement::parse(it));
    
    t = nextToken(it);
    if(t.type != BRACE_CLOSE){
        std::cerr << "Function: expected '}'\n";
        exit(1);
    }
    // func->children.push_back(expression::parse(it));
    return func;

}

void function::print(){
    std::cout << "FUNCTION: " << value << "\n";

    for(std::shared_ptr<symbol> s : children){
        s->print();
    }
}


class program : public typedSymbol<std::string>
{
private:
    /* data */
    program();
public:
    virtual void print();
    static program *parse(std::list<token>);
    ~program();
};

program::program()
{
    type = PROGRAM;
}

program *program::parse(std::list<token> tokens){

    program *prog = new program();
    std::list<token>::iterator it = tokens.begin();
    /* Do parsing */
    while(tokens.size() > 0){
        prog->children.push_back(function::parse(it));
        /*Remove list items from begin -> it*/
        while(tokens.begin() != it){
            tokens.pop_front();
        }
    }

    return prog;

}

void program::print(){
    std::cout << "PROGRAM:\n";
    for(std::shared_ptr<symbol> s : children){
        s->print();
    }
}

}

#endif