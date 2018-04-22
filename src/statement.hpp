#ifndef BRK_STATEMENT_HPP
#define BRK_STATEMENT_HPP

#include <memory>

class Statement {
    virtual ~Statement() {}
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(std::unique_ptr<Expression> e) : 
        e(std::move(e)) { }
    
    std::unique_ptr<Expression> e;
private:
};

class DeclarationStatement : public ExpressionStatement{

};

class CompoundStatement : public Statement {
public:
    CompoundStatement(std::unique_ptr<std::vector<Statement>> vec) : 
        statements(std::move(vec)) { }
    CompoundStatement(std::unique_ptr<Statement> s1, std::unique_ptr<Statement> s2);
    
    std::unique_ptr<std::vector<Statement>> statements;
private:
};

class ScopeStatement : public Statement {
public:
    ScopeStatement(std::unique_ptr<Statement> s) :
        s(std::move(s)) { }

    std::unique_ptr<Statement> s;
private:
};

class WhileStatement : public Statement {
public:
    WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body) :
        condition(std::move(condition)), body(std::move(body)) { }

    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;
private:
};

class DoStatement : public Statement {
public:
    DoStatement(std::unique_ptr<Statement> body, std::unique_ptr<Expression> condition) :
        body(std::move(body)), condition(std::move(condition)) { }

    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;
private:
};

class ForStatement : public Statement {
public:
    ForStatement(std::unique_ptr<Statement> init, std::unique_ptr<Expression> condition,
        std::unique_ptr<Expression> increment, std::unique_ptr<Statement> body) : 
            init(std::move(init)), condition(std::move(condition)), increment(std::move(increment)), body(std::move(body)) { }

    std::unique_ptr<Statement> init;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> increment;
    std::unique_ptr<Statement> body;
private:
};

class IfStatement : public Statement {
public:
    IfStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> ifBody, 
        std::unique_ptr<Statement> elseBody) :
            condition(std::move(condition)), ifBody(std::move(ifBody)), elseBody(std::move(elseBody)) { }


    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> ifBody;
    std::unique_ptr<Statement> elseBody;
private:
};

class ConditionalStatement : public Statement {
public:
private:
};

class SwitchStatement : public Statement {
public:
private:
};

class CaseStatement : public Statement {
public:
private:
};

class DefaultStatement : public Statement {
public:
private:
};

class ReturnStatement : public Statement {
public:
private:
};

class BreakStatement : public Statement {
public:
private:
};

class ContinueStatement : public Statement {
public:
private:
};

class GotoStatement : public Statement {
public:
private:
};

class LabelStatement : public Statement {
public:
private:
};

class AsmStatement : public Statement {
public:
private:
};

#endif //BRK_STATEMENT_HPP