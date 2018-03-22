#include "parser.hpp"
#include <string> //TODO: Make token contain union instead of numbers be strings. Oskar Mendel 2018-03-22

#include <iostream> //TODO: Remove this when testing is done. Oskar Mendel 2018-03-21

Parser::Parser(std::string t_content) : lexer(t_content), parsedTokens(0) {

}

Parser::~Parser() {

}

void Parser::parse() {
    this->currentToken = this->lexer.getToken();
    
    switch (currentToken.type) {
    case TOKEN_EOF:
        return;
    case TOKEN_VOID: // This is a type such as void or int means that a variable or function is declared
        // isFunction() TODO: Oskar Mendel 2018-03-22
        std::cout << "Found void" << std::endl;
        this->parseDefinition(currentToken);
        break;
    default:
        this->parseExpression();
    }
}

void Parser::parseDefinition(Token t) {
    Token type = t;
    std::cout << "Parsing definition" << std::endl;

    // Get identifier
    Token identifier = this->lexer.getToken();

    // If its not an identifier we got something weird..
    if (identifier.type != TOKEN_IDENTIFIER) {
        std::cout << "Expected identifier.. " << std::endl;
    }
    
    Token next = this->lexer.getToken();

    switch (next.type) {
        case TOKEN_OPENPAREN:
            std::cout << "This is a function" << std::endl;
            break;
        default:
            std::cout << "Something else was found" << std::endl;
            break;
    }

    // Peek next and if its an open paren we parse a function
    // Else we parse a variable
}

void Parser::parseExpression() {
    // TODO: Handle binary expressions here as well..
    std::cout << "This is a Expression" << std::endl;
    this->parsePrimary();
}

void Parser::parsePrimary() {

   //TODO: A lot of missing tokens to match on here.. Need to be added. Oskar Mendel 2018-03-20
   switch (this->currentToken.type) {
       case TOKEN_IDENTIFIER:
           //this->parseIdentifier(); //TODO: Oskar Mendel 2018-03-22
           break;
       case TOKEN_INTEGER: // TODO: Should theese fall through? Oskar Mendel 2018-03-20
           {auto res = this->parseNumber();
           std::cout << "Number: " << res->m_value << std::endl;}
           break;
       case TOKEN_FLOATING:
           break;
       case TOKEN_OPENPAREN:
           //this->parseParenExpression();
           break;
       case TOKEN_SEMICOLON:
           //TODO: Empty statement? Oskar Mendel 2018-03-20
           break;
   }
}

std::unique_ptr<NumberExpression> Parser::parseNumber() {

    std::cout << "Parsing a number" << std::endl;
    int s = stoi(currentToken.str);
    auto res = std::make_unique<NumberExpression>(s);
    // Consume number token..
    return std::move(res);
}