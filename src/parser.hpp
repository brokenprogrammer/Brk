#ifndef BRK_PARSER_HPP
#define BRK_PARSER_HPP

#include "lexer.hpp"
#include "expression.hpp"
#include <memory>
#include <vector>

class Parser {
public:
    Parser(std::string t_content);
    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;
    ~Parser();

    void parse();

private:
    std::unique_ptr<Expression> parsePrimaryExpression();
    std::unique_ptr<Expression> parsePostExpression(std::unique_ptr<Expression> e);
    std::unique_ptr<Expression> parseUnaryExpression();
    std::unique_ptr<Expression> parseCastExpression();
    std::unique_ptr<Expression> parseMultExpression();
    std::unique_ptr<Expression> parseAddExpression();
    std::unique_ptr<Expression> parseShiftExpression();
    std::unique_ptr<Expression> parseEqualityExpression();
    std::unique_ptr<Expression> parseAndExpression();
    std::unique_ptr<Expression> parseXorExpression();
    std::unique_ptr<Expression> parseOrExpression();
    std::unique_ptr<Expression> parseLogicalAndExpression();
    std::unique_ptr<Expression> parseLogicalOrExpression();
    std::unique_ptr<Expression> parseConditionalExpression();
    std::unique_ptr<Expression> parseAssignExpression();
    std::unique_ptr<Expression> parseExpression();

    Lexer lexer;
    //int parsedTokens;
    Token currentToken;
    std::vector<Token> tokens;
};

#endif //BRK_PARSER_HPP