#include "parser.hpp"

#include <iostream> //TODO: Remove this when testing is done. Oskar Mendel 2018-03-21

Parser::Parser(std::string t_content) : lexer(t_content), parsedTokens(0) {

}

Parser::~Parser() {

}

void Parser::parse() {
    Token currentToken = this->lexer.getToken();
    
    switch (currentToken.type) {
    case TOKEN_EOF:
        return;
    case TOKEN_VOID: // This is a type such as void or int means that a variable or function is declared
        std::cout << "Found void" << std::endl;
        this->parseDefinition(currentToken);
        break;
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

// This is commented out for now for testing purposes..

//void Parser::parsePrimary() {
//    int currentToken = 1; //TODO: Parser needs access to the Lexer.. Oskar Mendel 2018-03-20
//
//    //TODO: A lot of missing tokens to match on here.. Need to be added. Oskar Mendel 2018-03-20
//    switch (currentToken) {
//        case TOKEN_IDENTIFIER:
//            this->parseIdentifier();
//            break;
//        case TOKEN_INTEGER: // TODO: Should theese fall through? Oskar Mendel 2018-03-20
//            break;
//        case TOKEN_FLOATING:
//            this->parseNumber();
//            break;
//        case TOKEN_OPENPAREN:
//            this->parseParenExpression();
//            break;
//        case TOKEN_RETURN:
//            this->parseReturn();
//            break;
//        case TOKEN_OPENBRACE:
//            this->parseBlock();
//            break;
//        case TOKEN_SEMICOLON:
//            //TODO: Empty statement? Oskar Mendel 2018-03-20
//            break;
//    }
//}