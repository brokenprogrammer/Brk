#ifndef BRK_EXPRESSION_HPP
#define BRK_EXPRESSION_HPP

#include <memory>

class Expression {
public:
    virtual ~Expression() {}

private:
};

class UnaryExpression : public Expression {
public:
    UnaryExpression(std::unique_ptr<Expression> e) :
        e(std::move(e)) {}

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

class IdentifierExpression {

};

class IntegerExpression {

};

class FloatingExpression {

};

class StringExpression {

};

class PostIncrementExpression {

};

class PostDecrementExpression {

};

class CallExpression {

};

class ArrayExpression {
    
};

class NotExpression {

};

class ComplementExpression {

};

class NegativeExpression {

};

class PointerExpression {

};

class AddressExpression {

};

class CastExpression {

};

class MultExpression {

};

class DivideExpression {

};

class ModExpression {

};

class AddExpression {

};

class SubExpression {

};

class ShrExpression {

};

class ShlExpression {

};

class EqualityExpression {

};

class AndExpression {

};

class XorExpression {

};

class OrExpression {

};

class LogicalAndExpression {

};

//TODO: Binary Oskar Mendel 2018-03-23
class LogicalOrExpression {

};

//TODO: Binary Oskar Mendel 2018-03-23
class ConditionalExpression {

};

//TODO: Binary Oskar Mendel 2018-03-23
class AssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class AddAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class SubAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class MulAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class DivAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class ModAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class AndAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class OrAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class XorAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class ShlAssignExpression {

};

//TODO: Binary Assign? Oskar Mendel 2018-03-23
class ShrAssignExpression {

};

//TODO: Binary Oskar Mendel 2018-03-23
class CommaExpression : public BinaryExpression {
public:
    CommaExpression(std::unique_ptr<Expression> LHS, std::unique_ptr<Expression> RHS)
        :  BinaryExpression(std::move(LHS), std::move(RHS)) { }

private:
};

#endif //BRK_EXPRESSION_HPP