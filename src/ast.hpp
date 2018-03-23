#ifndef BRK_AST_HPP
#define BRK_AST_HPP

class Expression {
public:
    virtual ~Expression() {}
};

class NumberExpression : public Expression {
public:
    NumberExpression(double t_value) : m_value(t_value);

    double m_value;
private:
};

class VariableExpression : public Expression {
public:
    VariableExpression(const std::string &t_name) : m_name(t_name);

    std::string m_name;
private:
};

#endif //BRK_AST_HPP