#include "parser.hpp"

Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::parse() {

    while (parsedTokens < tokens.length) {
        //TODO: Parse each statement.. Oskar Mendel 2018-03-21
        this->parseTop();
    }
}

void Parser::parseTop() {
    switch (currentToken) {
        case TOKEN_EOF:
            return;
        case TOKEN_TYPE: // This is a type such as void or int means that a variable or function is declared
            this->parseDefinition();
            break;
    }
}

void Parser::parseDefinition() {
    Token type = currentToken;
    getNextToken(); // Here we eat the type token and advance to the next token

    // Get identifier
    
    // Peek next and if its an open paren we parse a function
    // Else we parse a variable
}

// TODO: Better name for this? Oskar Mendel 2018-03-20
void Parser::parsePrimary() {
    int currentToken = 1; //TODO: Parser needs access to the Lexer.. Oskar Mendel 2018-03-20

    //TODO: A lot of missing tokens to match on here.. Need to be added. Oskar Mendel 2018-03-20
    switch (currentToken) {
        case TOKEN_IDENTIFIER:
            this->parseIdentifier();
            break;
        case TOKEN_INTEGER: // TODO: Should theese fall through? Oskar Mendel 2018-03-20
            break;
        case TOKEN_FLOATING:
            this->parseNumber();
            break;
        case TOKEN_OPENPAREN:
            this->parseParenExpression();
            break;
        case TOKEN_RETURN:
            this->parseReturn();
            break;
        case TOKEN_OPENBRACE:
            this->parseBlock();
            break;
        case TOKEN_SEMICOLON:
            //TODO: Empty statement? Oskar Mendel 2018-03-20
            break;
    }
}