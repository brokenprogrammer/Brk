#ifndef BRK_PARSER_HPP
#define BRK_PARSER_HPP

#include "lexer.hpp"
#include <memory>
#include <vector>

class Expression {
public:
    virtual ~Expression() {}
};

class NumberExpression : public Expression {
public:
    NumberExpression(double t_value) : m_value(t_value) {}

    double m_value;
private:
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
    void parseExpression();
    void parsePrimary();
    std::unique_ptr<NumberExpression> parseNumber();

    Lexer lexer;

    int parsedTokens;
    Token currentToken;
    std::vector<Token> tokens;
};

#endif //BRK_PARSER_HPP