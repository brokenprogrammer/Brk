#include "parser.hpp"
#include <string> //TODO: Make token contain union instead of numbers be strings. Oskar Mendel 2018-03-22
#include <typeinfo> //TODO: Only used for testing..
#include <iostream> //TODO: Remove this when testing is done. Oskar Mendel 2018-03-21

Parser::Parser(std::string t_content) : lexer(t_content) {

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
        break;
    default:
        this->parseExpression();
        break;
    }
}

std::unique_ptr<Expression> Parser::parsePrimaryExpression() {
    std::unique_ptr<Expression> e;

    //TODO: Add all the primitive types expected, example: uint8 uint16 uint32.. int8.. 
        // Oskar Mendel 2018-03-24
    switch(this->currentToken.type) {
        case TOKEN_IDENTIFIER:
            e = std::unique_ptr<Expression>{new IdentifierExpression(this->currentToken.str)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_INTEGER:
            e = std::unique_ptr<Expression>{new IntegerExpression(stoi(this->currentToken.str))};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_FLOATING:
            e = std::unique_ptr<Expression>{new FloatingExpression(12.2f)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_CHAR: //TODO: Oskar Mendel 2018-03-24
            break;
        case TOKEN_STRING:
            e = std::unique_ptr<Expression>{new StringExpression(this->currentToken.str)};
            this->currentToken = this->lexer.getToken();
            break;
        default:
            // Error
            e = nullptr;
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            break;
    }

    return parsePostExpression(std::move(e));
}

std::unique_ptr<Expression> Parser::parsePostExpression(std::unique_ptr<Expression> e) {

    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_ADDADD:
                //e = new PostIncrementExpression(e);
                break;
            case TOKEN_SUBTRACTSUBTRACT:
                //e = new PostDecrementExpression(e);
                break;
            case TOKEN_PERIOD:
                // TODO: Advance Token
                if (this->currentToken.type == TOKEN_IDENTIFIER) {
                    //e = new DotIdentifierExpression(e, this->currentToken.src);
                } else {
                    // Error
                }
                break;
            case TOKEN_OPENPAREN:
                //e = new CallExpression(e, parseArguments());
                continue;
            case TOKEN_OPENBRACKET:
                {
                    // TODO: Advance Token
                    this->currentToken = this->lexer.getToken();
                    std::unique_ptr<Expression> i = parseExpression();
                    //e = new ArrayExpression(e, i);
                    // Verify that ']' is here..
                }
                continue;
            default:
                return e;
        }

        // TODO: Advance Token
        this->currentToken = this->lexer.getToken();
    }
}

std::unique_ptr<Expression> Parser::parseUnaryExpression() {
    std::unique_ptr<Expression> e;

    switch (this->currentToken.type) {
        case TOKEN_ADDADD:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new AddAssignExpression(e, new IntegerExpression(1));
            break;
        case TOKEN_SUBTRACTSUBTRACT:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new SubAssignExpression(e, new IntegerExpression(1));
            break;
        case TOKEN_AND:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new AddressExpression(e);
            break;
        case TOKEN_MULTIPLY:
            e = parseUnaryExpression();
            //e = new PointerExpression(e);
            break;
        case TOKEN_ADD:
            // TODO: Advance Token
            e = parseUnaryExpression();
            break;
        case TOKEN_SUBTRACT:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new NegativeExpression(e);
            break;
        case TOKEN_XOR:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new ComplementExpression(e);
            break;
        case TOKEN_NOT:
            // TODO: Advance Token
            e = parseUnaryExpression();
            //e = new NotExpression(e);
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
        // TODO: Advance Token
        //e = parseType();
        // verify current token is ')'
        e1 = parseUnaryExpression();
        //e = new CastExpression(e, e1);
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
            // TODO: Advance Token
            e1 = parseCastExpression();
            //e = new MultExpression(e, e1);
            break;
        case TOKEN_DIVIDE:
            // TODO: Advance Token
            e1 = parseCastExpression();
            //e = new DivideExpression(e, e1);
            break;
        case TOKEN_MOD:
            // TODO: Advance Token
            e1 = parseCastExpression();
            //e = new ModExpression(e, e1);
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
            // TODO: Advance Token
            e1 = parseMultExpression();
            //e = new AddExpression(e, e1);
            break;
        case TOKEN_SUBTRACT:
            // TODO: Advance Token
            e1 = parseMultExpression();
            //e = new SubExpression(e, e1);
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
            // TODO: Advance Token
            // e1 = parseAddExpression();
            // e = new ShlExpression(e, e1);
            break;
        case TOKEN_SHIFTRIGHT:
            // TODO: Advance Token
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
        case TOKEN_ISEQUAL:
        case TOKEN_NOTEQUAL:
            // TODO: Advance Token
            // e1 = parseShiftExpression();
            // e = new EqualityExpression(this->currentToken.type, e, e1);
            break;
        case TOKEN_LOWERTHAN:
        case TOKEN_GREATERTHAN:
        case TOKEN_LOWEROREQUALS:
        case TOKEN_GREATEROREQUALS:
            // TODO: Advance Token
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
        //TODO: Advance Token
        //e1 = parseEqualityExpression();
        //e = new AndExpression(e, e1);
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseXorExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseAndExpression();
    while (this->currentToken.type == TOKEN_XOR) {
        //TODO: Advance Token
        //e1 = parseAndExpression();
        //e = new XorExpression(e, e1);
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
        //TODO: Advance Token
        //e1 = parseOrExpression();
        //e = new LogicalAndExpression(TOKEN_LOGICALAND, e, e1);
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseLogicalOrExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseLogicalAndExpression();
    while (this->currentToken.type == TOKEN_LOGICALOR) {
        //TODO: Advance Token
        this->currentToken = this->lexer.getToken();
        e1 = parseLogicalAndExpression();
        e = std::unique_ptr<Expression>{new LogicalOrExpression(std::move(e), std::move(e1))};
    }
    return e;
}

std::unique_ptr<Expression> Parser::parseConditionalExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;
    std::unique_ptr<Expression> e2;

    e = parseLogicalOrExpression();
    if (this->currentToken.type == TOKEN_QUESTION) {
        //TODO: Advance Token
        this->currentToken = this->lexer.getToken();
        e1 = parseExpression();
        //Verify that current token is ':'
        if (!(this->currentToken.type == TOKEN_COLON)) {
            // Error
        }
        e2 = parseConditionalExpression();
        e = std::unique_ptr<Expression>{new ConditionalExpression(std::move(e), std::move(e1), std::move(e2))};
    }
    return e;
}

std::unique_ptr<Expression> Parser::parseAssignExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseConditionalExpression();
    while(1) {
        switch(this->currentToken.type) {
            case TOKEN_EQUAL:
                //TODO: TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new AssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_ADDEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new AddAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_SUBTRACTEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new SubAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_MULTIPLYEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new MulAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_DIVIDEEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new DivAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_MODEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new ModAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_ANDEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new AndAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_OREQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new OrAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_XOREQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new XorAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_SHIFTLEFTEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new ShlAssignExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_SHIFTRIGHTEQUAL:
                //TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAssignExpression();
                e = std::unique_ptr<Expression>{new ShrAssignExpression(std::move(e), std::move(e1))};
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

    e = parseAssignExpression();
    while (currentToken.type == TOKEN_COMMA) {
        this->currentToken = this->lexer.getToken();
        e1 = parseAssignExpression();
        e = std::unique_ptr<Expression>{new CommaExpression(std::move(e), std::move(e1))};
    }

    return e;
}