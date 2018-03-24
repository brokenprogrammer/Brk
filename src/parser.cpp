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

std::unique_ptr<Expression> Parser::parsePrimaryExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    switch(this->currentToken.type) {
        case TOKEN_IDENTIFIER:
            break;
        default:
            // Error
            e = nullptr;
            // Advance token
            break;
    }

    return parsePostExpression(e);
}

std::unique_ptr<Expression> Parser::parsePostExpression(std::unique_ptr<Expression> e) {

    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_ADDADD:
                break;
            case TOKEN_SUBTRACTSUBTRACT:
                break;
            case TOKEN_DOT:
                break;
            case TOKEN_MULTIPLY:
                break;
            case TOKEN_OPENPAREN:
                break;
            case TOKEN_OPENBRACKET:
                break;
            default:
                return e;
        }

        // advance token
    }
}

std::unique_ptr<Expression> Parser::parseUnaryExpression() {
    std::unique_ptr<Expression> e;

    switch (this->currentToken.type) {
        case TOKEN_ADDADD:
            // Advance token
            e = parseUnaryExpression();
            e = new AddAssignExpression(e, new IntegerExpression(1));
            break;
        case TOKEN_SUBTRACTSUBTRACT:
            // Advance token
            e = parseUnaryExpression();
            e = new SubAssignExpression(e, new IntegerExpression(1));
            break;
        case TOKEN_AND:
            // Advance token
            e = parseUnaryExpression();
            e = new AddressExpression(e);
            break;
        case TOKEN_MULTIPLY:
            e = parseUnaryExpression();
            e = new PointerExpression(e);
            break;
        case TOKEN_ADD:
            // Advance token
            e = parseUnaryExpression();
            break;
        case TOKEN_SUBTRACT:
            // Advance token
            e = parseUnaryExpression();
            e = new NegativeExpression(e);
            break;
        case TOKEN_TILDE:
            // Advance token
            e = parseUnaryExpression();
            e = new ComplementExpression(e);
            break;
        case TOKEN_NOT:
            // Advance tokne
            e = parseUnaryExpression();
            e = new NotExpression(e);
            break;
        //TODO: Add unary keyword "new", "delete" Oskar Mendel 2018-3-24 
        default:
            e = parsePrimaryExpression();
            break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseCastExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    if (this->currentToken.type == TOKEN_OPENPAREN) {
        // Advance token
        e = parseType();
        // verify current token is ')'
        e1 = parseUnaryExpression();
        e = new CastExpression(e, e1);
    } else {
        e = parseUnaryExpression();
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseMultExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseCastExpression();
    switch (this->currentToken.type) {
        case TOKEN_MULTIPLY:
            // Advance token
            e1 = parseCastExpression();
            e = new MultExpression(e, e1);
            break;
        case TOKEN_DIVIDE:
            // Advance token
            e1 = parseCastExpression();
            e = new MultExpression(e, e1);
            break;
        case TOKEN_MOD:
            // Advance token
            e1 = parseCastExpression();
            e = new MultExpression(e, e1);
            break;

        default:
            break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseAddExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseMultExpression();
    switch (this->currentToken.type) {
        case TOKEN_ADD:
            // Advance token
            e1 = parseMultExpression();
            e = new AddExpression(e, e1);
            break;
        case TOKEN_SUBTRACT:
            // Advance token
            e1 = parseMultExpression();
            e = new SubExpression(e, e1);
            break;

        default:
            break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseShiftExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseAddExpression();
    switch (this->currentToken.type) {
        case TOKEN_SHIFTLEFT:
            // Advance token
            // e1 = parseAddExpression();
            // e = new ShlExpression(e, e1);
            break;
        case TOKEN_SHIFTRIGHT:
            // Advance token
            // e1 = parseAddExpression();
            // e = new ShrExpression(e, e1);
            break;
        
        default:
            break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseEqualityExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseShiftExpression();
    switch(this->currentToken.type) {
        case TOKEN_EQUALEQUAL:
        case TOKEN_NOTEQUAL:
            // Advance token
            // e1 = parseShiftExpression();
            // e = new EqualityExpression(this->currentToken.type, e, e1);
            break;
        case TOKEN_LESSTHAN:
        case TOKEN_GREATERTHAN:
        case TOKEN_LESSOREQUAL:
        case TOKEN_GREATEROREQUAL:
            // Advance token
            // e1 = parseShiftExpression();
            // e = new EqualityExpression(this->currentToken.type, e, e1);
        default:
            break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseAndExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseEqualityExpression();
    while (this->currentToken.type == TOKEN_AND) {
        //Advance token
        //e1 = parseEqualityExpression();
        e = new AndExpression(e, e1);
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseXorExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseAndExpression();
    while (this->currentToken.type == TOKEN_XOR) {
        //Advance token
        //e1 = parseAndExpression();
        e = new XorExpression(e, e1);
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseOrExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseXorExpression();
    while (this->currentToken.type == TOKEN_OR) {
        //AdvanceToken
        //e1 = parseXorExpression();
        //e = new OrExpression(e, e1);
    }
    
    return e;
}

std::unique_ptr<Expression> Parser::parseLogicalAndExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseOrExpression();
    while (this->currentToken.type == TOKEN_LOGICALAND) {
        //Advance token
        //e1 = parseOrExpression();
        //e = new LogicalAndExpression(TOKEN_LOGICALAND, e, e1);
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseLogicalOrExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    //e = parseLogicalAndExpression();
    while (this->currentToken.type == TOKEN_LOGICALOR) {
        //Advance token
        //e1 = parseLogicalAndExpression();
        //e = new LogicalOrExpression(e, e1);
    }
    return e;
}

std::unique_ptr<Expression> Parser::parseConditionalExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    //e = parseLogicalOrExpression();

    if (this->currentToken.type == TOKEN_QUESTION) {
        //Advance token
        //e1 = parseExpression();
        //Verify that current token is ':'
        //e2 = parseConditionalExpression();
        //e = new ConditionalExpression(e, e1, e2);
    }
    return e;
}

std::unique_ptr<Expression> Parser::parseAssignExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    //e = parseConditionalExpression();
    while(1) {
        switch(this->currentToken.type) {
            case TOKEN_ASSIGN:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new AssignExpression(e, e1);
                continue;
            case TOKEN_ADDEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new AddAssignExpression(e, e1);
                continue;
            case TOKEN_SUBTRACTEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new SubAssignExpression(e, e1);
                continue;
            case TOKEN_MULTIPLYEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new MulAssignExpression(e, e1);
                continue;
            case TOKEN_DIVIDEEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new DivAssignExpression(e, e1);
                continue;
            case TOKEN_MODEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new ModAssignExpression(e, e1);
                continue;
            case TOKEN_ANDEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new AndAssignExpression(e, e1);
                continue;
            case TOKEN_OREQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new OrAssignExpression(e, e1);
                continue;
            case TOKEN_XOREQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new XorAssignExpression(e, e1);
                continue;
            case TOKEN_SHIFTLEFTEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new ShlAssignExpression(e, e1);
                continue;
            case TOKEN_SHIFTRIGHTEQUAL:
                //Advance token
                //e1 = parseAssignExpression();
                //e = new ShrAssignExpression(e, e1);
                continue;
            default:
                break;
        }
        break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    //e = parseAssignExpression();
    while (currentToken.type == TOKEN_COMMA) {
        this->currentToken = this->lexer.getToken();
        //e1 = parseAssignExpression();
        //e = new CommaExpression(e, e1);
    }

    return e;
}