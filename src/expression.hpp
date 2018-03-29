#ifndef BRK_EXPRESSION_HPP
#define BRK_EXPRESSION_HPP

#include "globals.hpp"
#include "identifier.hpp"
#include "lexer.hpp" //TODO: Change later when tokens are split into token.hpp
#include <memory>       // Oskar Mendel 2018-03-27

class Expression {
public:
    virtual ~Expression() {}

private:
};

class UnaryExpression : public Expression {
public:
    UnaryExpression(std::unique_ptr<Expression> e) :
        e(std::move(e)) { }

    std::unique_ptr<Expression> e;

private:
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

private:
};

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(const std::string &t_identifier)
        : m_identifier(t_identifier) { }

    // TODO: IdentifierExpression that uses a declaration - Oskar Mendel 2018-03-26

    //TODO: This should be some form of pointer. Oskar Mendel 2018-03-27
    Identifier m_identifier;
private:
};

class IntegerExpression : public Expression {
public:
    IntegerExpression(double t_value) : m_value(t_value) { }

    llvm::Value* codegen();

    double m_value;

private:
};

class FloatingExpression : public Expression {
public:
    FloatingExpression(double t_value) : m_value(t_value) { }

    long long m_value;

private:
};

class StringExpression : public Expression {
public:
    StringExpression(const std::string &t_value) : m_value(t_value) { }

    std::string m_value;

private:
};

class PostIncrementExpression : public BinaryExpression {
public:
    // TODO: Later implement this in .cpp Oskar Mendel 2018-03-27
    PostIncrementExpression(std::unique_ptr<Expression> e);

private:
};

class PostDecrementExpression : public BinaryExpression {
public:
    // TODO: Later implement this in .cpp Oskar Mendel 2018-03-27
    PostDecrementExpression(std::unique_ptr<Expression> e);

private:
};

//TODO: Should take an array of arguments.. Oskar Mendel 2018-03-27
class CallExpression : public UnaryExpression{
public:
    CallExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class ArrayExpression : public BinaryExpression {
public:
    ArrayExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class NotExpression : public UnaryExpression{
public:
    NotExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class ComplementExpression : public UnaryExpression{
public:
    ComplementExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class NegativeExpression : public UnaryExpression{
public:
    NegativeExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class PointerExpression : public UnaryExpression{
public:
    PointerExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class AddressExpression : public UnaryExpression{
public:
    AddressExpression(std::unique_ptr<Expression> e)
        : UnaryExpression(std::move(e)) { }

private:
};

class CastExpression : public UnaryExpression {
public:
    //TODO: Takes a type and an expression. 
        // Oskar Mendel 2018-03-27
private:
};

class MultExpression : public BinaryExpression {
public:
    MultExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class DivideExpression : public BinaryExpression {
public:
    DivideExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class ModExpression : public BinaryExpression {
public:
    ModExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class AddExpression : public BinaryExpression {
public:
    AddExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class SubExpression : public BinaryExpression {
public:
    SubExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class ShrExpression : public BinaryExpression {
public:
    ShrExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class ShlExpression : public BinaryExpression {
public:
    ShlExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class EqualityExpression : public BinaryExpression {
public:
    EqualityExpression(TokenType t_type, std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)), m_type(t_type) { }

    TokenType m_type;
private:
};

class AndExpression : public BinaryExpression {
public:
    AndExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class XorExpression : public BinaryExpression {
public:
    XorExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class OrExpression : public BinaryExpression {
public:
    OrExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class LogicalAndExpression : public BinaryExpression {
public:
    LogicalAndExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class LogicalOrExpression : public BinaryExpression {
public:
    LogicalOrExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class ConditionalExpression : public BinaryExpression {
public:
    ConditionalExpression(std::unique_ptr<Expression> cond, 
        std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
            : BinaryExpression(std::move(LHS), std::move(RHS)), m_cond(std::move(cond)) { }
    
    std::unique_ptr<Expression> m_cond;
private:
};

class AssignExpression : public BinaryExpression {
public:
    AssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class AddAssignExpression : public BinaryExpression {
public:
    AddAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class SubAssignExpression : public BinaryExpression {
public:
    SubAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class MulAssignExpression : public BinaryExpression {
public:
    MulAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class DivAssignExpression : public BinaryExpression {
public:
    DivAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class ModAssignExpression : public BinaryExpression {
public:
    ModAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class AndAssignExpression : public BinaryExpression {
public:
    AndAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class OrAssignExpression : public BinaryExpression{
public:
    OrAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class XorAssignExpression : public BinaryExpression {
public:
    XorAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class ShlAssignExpression : public BinaryExpression {
public:
    ShlAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }
        
private:
};

class ShrAssignExpression : public BinaryExpression {
public:
    ShrAssignExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        : BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

class CommaExpression : public BinaryExpression {
public:
    CommaExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        :  BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

#endif //BRK_EXPRESSION_HPP