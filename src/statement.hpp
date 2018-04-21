#ifndef BRK_STATEMENT_HPP
#define BRK_STATEMENT_HPP

class Statement {
    virtual ~Statement() {}
};

class ExpressionStatement : public Statement {

};

class DeclarationStatement : public ExpressionStatement{

};

class CompoundStatement : public Statement {

};

class ScopeStatement : public Statement {

};

class WhileStatement : public Statement {

};

class DoStatement : public Statement {

};

class ForStatement : public Statement {

};

class IfStatement : public Statement {

};

class ConditionalStatement : public Statement {

};

class SwitchStatement : public Statement {

};

class CaseStatement : public Statement {

};

class DefaultStatement : public Statement {

};

class ReturnStatement : public Statement {

};

class BreakStatement : public Statement {

};

class ContinueStatement : public Statement {

};

class GotoStatement : public Statement {

};

class LabelStatement : public Statement {

};

class AsmStatement : public Statement {

};

#endif //BRK_STATEMENT_HPP