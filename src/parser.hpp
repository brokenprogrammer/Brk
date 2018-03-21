#ifndef BRK_PARSER_HPP
#define BRK_PARSER_HPP

#include "lexer.hpp"
#include <vector>

class Expression {
public:
    virtual ~Expression() {}
};

class NumberExpression : public Expression {
public:
    NumberExpression(double t_value) : m_value(t_value) {}

private:
    double m_value;
};

class Parser {
public:
    Parser(std::string t_content);
    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;
    ~Parser();

    void parse();
private:
    
    // Should return an expression AST?
    void parseDefinition(Token t);

    Lexer lexer;

    int parsedTokens;
    std::vector<Token> tokens;
};

#endif //BRK_PARSER_HPP