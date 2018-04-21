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
        std::unique_ptr<Expression> e = this->parseExpression();
        auto ir = e->codegen();
        ir->print(llvm::errs(), nullptr);
        std::cout << std::endl;
        break;
    }
}

std::unique_ptr<Statement> Parser::parseStatement() {
    std::unique_ptr<Statement> s;
    Token *t;

    switch (this->currentToken.type) {
        case TOKEN_IDENTIFIER:
            // Look ahead to see if its a decl, label or expression.
            // t = this->lexer.peek();
            if (t.value == TOKEN_SEMICOLON) { // Check if its a label
                Identifier *identifier;
                //identifier = this->currentToken.str;

                this->currentToken = this->lexer.getToken(); //Eat Identifier
                this->currentToken = this->lexer.getToken(); //Eat Semicolon

                s = parseStatement();
                //s = std::unique_ptr<Statement>{new LabelStatement()};
            } else if (isDeclaration()) {
                //TODO: Oskar Mendel 2018-04-22
            } else {
                std::unique_ptr<Expression> expression;
                expression = parseExpression();

                // Check that current token is a ';'
                //s = std::unique_ptr<Statement>{new ExpressionStatement()};
            } break;
        case TOKEN_UINT32:
        case TOKEN_INT32:
        case TOKEN_UINT64:
        case TOKEN_INT64:
        case TOKEN_FLOAT32:
        case TOKEN_FLOAT64:
        case TOKEN_STRING:
        case TOKEN_OPENPAREN:
        case TOKEN_MULTIPLY:
        case TOKEN_SUBTRACT:
        case TOKEN_ADD:
        case TOKEN_ADDADD:
        case TOKEN_SUBTRACTSUBTRACT:
            {
                std::unique_ptr<Expression> expression;
                expression = parseExpression();
                // Check that current token is a ';'
                //s = std::unique_ptr<Statement>{new ExpressionStatement()};
            } break;
        case TOKEN_AUTO:
        case TOKEN_CONST:
            {

            } break;
        /*case TOKEN_STRUCT:        TODO: Oskar Mendel 2018-04-22
        case TOKEN_UNION:
        case TOKEN_CLASS:
        case TOKEN_ENUM:
            break; */
        case TOKEN_OPENBRACE:
            {
                // Array *statements
                while (this->currentToken.value != TOKEN_CLOSEBRACE) {
                    // Array push (parseStatement())
                }
                //s = std::unique_ptr<Statement>{new CompoundStatement()};

                this->currentToken = this->lexer.getToken();
            } break;
        case TOKEN_WHILE:
            {
                std::unique_ptr<Expression> condition;
                std::unique_ptr<Statement> body;

                this->currentToken = this->lexer.getToken();
                // Check that current token is '('
                condition = parseExpression();
                // Check that current token is ')'
                body = parseStatement();
                s = std::unique_ptr<Statement>{new WhileStatement()};
            } break;
        case TOKEN_SEMICOLON:
            if (false) {
                // Error use {} for empty expression not ';'
            }
            this->currentToken = this->lexer.getToken();
            s = std::unique_ptr<Statement>{new ExpressionStatement()};
            break;
        case TOKEN_DO:
            {
                std::unique_ptr<Expression> condition;
                std::unique_ptr<Statement> body;

                this->currentToken = this->lexer.getToken();

                body = parseStatement();
                // Check current token is 'while'
                // Check current token is '('
                condition = parseExpression();
                // Check current token is ')'
                s = std::unique_ptr<Statement>{new DoStatement()};
            } break;
        case TOKEN_FOR:
            {
                std::unique_ptr<Statement> init;
                std::unique_ptr<Expression> condition;
                std::unique_ptr<Expression> increment;
                std::unique_ptr<Statement> body;

                this->currentToken = this->lexer.getToken();

                //Check current token is '('
                if (this->currentToken.value == TOKEN_SEMICOLON) {
                    init = nullptr;
                    this->currentToken = this->lexer.getToken();
                } else {
                    init = parseStatement();
                }

                if (this->currentToken.value == TOKEN_SEMICOLON) {
                    condition = nullptr;
                    this->currentToken = this->lexer.getToken();
                } else {
                    condition = parseExpression();
                    // Check current token is ';'
                }

                if (this->currentToken.value == TOKEN_CLOSEPAREN) {
                    increment = nullptr;
                    this->currentToken = this->lexer.getToken();
                } else {
                    increment = parseExpression();
                    // Check current token is ')'
                }

                body = parseStatement();
                s = std::unique_ptr<Statement>{new ForStatement()};
            } break;
        case TOKEN_IF:
            {
                std::unique_ptr<Expression> condition;
                std::unique_ptr<Statement> ifBody;
                std::unique_ptr<Statement> elseBody;

                this->currentToken = this->lexer.getToken();

                // Check current token is '('
                condition = parseExpression();
                // check current token is ')'

                if  (this->currentToken.value == TOKEN_ELSE) {
                    this->currentToken = this->lexer.getToken();
                    elseBody = parseStatement();
                } else {
                    elseBody = nullptr;
                }

                s = std::unique_ptr<Statement>{new IfStatement()};
            } break;
        case TOKEN_SWITCH:
            {
                std::unique_ptr<Expression> condition;
                std::unique_ptr<Statement> body;

                this->currentToken = this->lexer.getToken();
                // Check current token is '('
                condition = parseExpression();
                // check current token is ')'
                body = parseStatement();
                s = std::unique_ptr<Statement>{new SwitchStatement()};
            } break;
        case TOKEN_CASE:
            {   
                std::unique_ptr<Expression> expression;
                // Array* statements

                this->currentToken = this->lexer.getToken();
                expression = parseExpression();
                // check current token is ':'

                while (this->currentToken.value != TOKEN_CASE &&
                        this->currentToken.value != TOKEN_DEFAULT &&
                        this->currentToken.value != TOKEN_CLOSEBRACE) {
                    // statements push (parseStatement())
                }

                s = std::unique_ptr<Statement>{new CompoundStatement()};
                s = std::unique_ptr<Statement>{new ScopeStatement()};
                s = std::unique_ptr<Statement>{new CaseStatement()};
            } break;
        case TOKEN_DEFAULT:
            {
                // Array* statements
                this->currentToken = this->lexer.getToken();
                // check current token is ':'
                
                while (this->currentToken.value != TOKEN_CASE &&
                        this->currentToken.value != TOKEN_DEFAULT &&
                        this->currentToken.value != TOKEN_CLOSEBRACE) {
                    // statements push (parseStatement())
                }

                s = std::unique_ptr<Statement>{new CompoundStatement()};
                s = std::unique_ptr<Statement>{new ScopeStatement()};
                s = std::unique_ptr<Statement>{new DefaultStatement()};
            } break;
        case TOKEN_RETURN:
            {
                std::unique_ptr<Expression> expression;

                this->currentToken = this->lexer.getToken();
                
                if (this->currentToken.value == TOKEN_SEMICOLON) {
                    expression = nullptr;
                } else {
                    expression = parseExpression();
                }

                // Check that current token is ';'
                s = std::unique_ptr<Statement>{new ReturnStatement()};
            } break;
        case TOKEN_BREAK:
            {
                Identifier *identifier;

                this->currentToken = this->lexer.getToken();

                if (this->currentToken.value == TOKEN_IDENTIFIER) {
                    identifier = this->currentToken.str;
                    this->currentToken = this->lexer.getToken();
                } else {
                    identifier = nullptr;
                }
                // Check that current token is ';'
                s = std::unique_ptr<Statement>{new BreakStatement()};
            } break;
        case TOKEN_CONTINUE:
            {
                Identifier *identifier;

                this->currentToken = this->lexer.getToken();

                if (this->currentToken.value == TOKEN_IDENTIFIER) {
                    identifier = this->currentToken.str;
                    this->currentToken = this->lexer.getToken();
                } else {
                    identifier = nullptr;
                }
                // Check that current token is ';'
                s = std::unique_ptr<Statement>{new ContinueStatement()};
            } break;
        /*case TOKEN_GOTO:
        case TOKEN_LABEL:
        case TOKEN_ASM:
            break; */
        default:
            // Error "found token.toChars() instead of statement" TODO: Oskar Mendel 2018-04-22
            s = nullptr;
            break;

    }
}

//TODO: Not implemented - Oskar Mendel 2018-03-27
// TODO: Null
// TODO:
std::unique_ptr<Expression> Parser::parsePrimaryExpression() {
    std::unique_ptr<Expression> e;

    switch(this->currentToken.type) {
        case TOKEN_IDENTIFIER:
            e = std::unique_ptr<Expression>{new IdentifierExpression(this->currentToken.str)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_UINT32:
            e = std::unique_ptr<Expression>{new IntegerExpression(this->currentToken.int64Val, TOKEN_UINT32)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_INT32:
            e = std::unique_ptr<Expression>{new IntegerExpression(this->currentToken.int64Val, TOKEN_INT32)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_UINT64:
            e = std::unique_ptr<Expression>{new IntegerExpression(this->currentToken.int64Val, TOKEN_UINT64)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_INT64:
            e = std::unique_ptr<Expression>{new IntegerExpression(this->currentToken.int64Val, TOKEN_INT64)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_FLOAT32:
            e = std::unique_ptr<Expression>{new FloatingExpression((float)this->currentToken.float64Val)};
            this->currentToken = this->lexer.getToken();
            break;
        case TOKEN_FLOAT64:
            e = std::unique_ptr<Expression>{new FloatingExpression(this->currentToken.float64Val)};
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

//TODO: Not implemented - Oskar Mendel 2018-03-27
std::unique_ptr<Expression> Parser::parsePostExpression(std::unique_ptr<Expression> e) {

    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_ADDADD:
                //e = std::unique_ptr<Expression>{new PostIncrementExpression(std::move(e))};
                break;
            case TOKEN_SUBTRACTSUBTRACT:
                //e = std::unique_ptr<Expression>{new PostDecrementExpression(std::move(e))};
                break;
            case TOKEN_PERIOD:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                if (this->currentToken.type == TOKEN_IDENTIFIER) {
                    //e = std::unique_ptr<Expression>{new DotIdentifierExpression(e, this->currentToken.src)};
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

//TODO: Add keywords
std::unique_ptr<Expression> Parser::parseUnaryExpression() {
    std::unique_ptr<Expression> e;

    switch (this->currentToken.type) {
        case TOKEN_ADDADD:
            {
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e = parseUnaryExpression();
                std::unique_ptr<Expression> e1 = std::unique_ptr<Expression>{new IntegerExpression(1, TOKEN_UINT32)};
                e = std::unique_ptr<Expression>{new AddAssignExpression(std::move(e), std::move(e1))};
            }
            break;
        case TOKEN_SUBTRACTSUBTRACT:
            {
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e = parseUnaryExpression();
                std::unique_ptr<Expression> e1 = std::unique_ptr<Expression>{new IntegerExpression(1, TOKEN_UINT32)};
                e = std::unique_ptr<Expression>{new SubAssignExpression(std::move(e), std::move(e1))};
            }
            break;
        case TOKEN_AND:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            e = std::unique_ptr<Expression>{new AddressExpression(std::move(e))};
            break;
        case TOKEN_MULTIPLY:
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            e = std::unique_ptr<Expression>{new PointerExpression(std::move(e))};
            break;
        case TOKEN_ADD:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            break;
        case TOKEN_SUBTRACT:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            e = std::unique_ptr<Expression>{new NegativeExpression(std::move(e))};
            break;
        case TOKEN_XOR:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            e = std::unique_ptr<Expression>{new ComplementExpression(std::move(e))};
            break;
        case TOKEN_NOT:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseUnaryExpression();
            e = std::unique_ptr<Expression>{new NotExpression(std::move(e))};
            break;
        case TOKEN_OPENPAREN:
            //TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e = parseExpression();
            if (!(this->currentToken.type == TOKEN_CLOSEPAREN)) {
                //Error
            }
            this->currentToken = this->lexer.getToken();
            break;
        //TODO: Add unary keyword "new", "delete" Oskar Mendel 2018-3-24 
        default:
            e = parsePrimaryExpression();
            break;
    }

    return e;
}

//TODO: Not implemented - Oskar Mendel 2018-03-27
//TODO: Implement this when types etc are ready, this might be combined with another function?
//      Oskar Mendel 2018-03-27
std::unique_ptr<Expression> Parser::parseCastExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    if (this->currentToken.type == TOKEN_OPENPAREN) {
        // TODO: Advance Token
        // PEEK and find typename else just parse unary expression. 
        //e = parseType();
        // verify current token is ')'
        e = parseUnaryExpression();
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
    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_MULTIPLY:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseCastExpression();
                e = std::unique_ptr<Expression>{new MultExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_DIVIDE:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseCastExpression();
                e = std::unique_ptr<Expression>{new DivideExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_MOD:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseCastExpression();
                e = std::unique_ptr<Expression>{new ModExpression(std::move(e), std::move(e1))};
               continue;

            default:
                break;
        }
        break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseAddExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseMultExpression();
    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_ADD:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseMultExpression();
                e = std::unique_ptr<Expression>{new AddExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_SUBTRACT:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseMultExpression();
                e = std::unique_ptr<Expression>{new SubExpression(std::move(e), std::move(e1))};
                continue;

            default:
                break;
        }
        break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseShiftExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseAddExpression();
    while(1) {
        switch (this->currentToken.type) {
            case TOKEN_SHIFTLEFT:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAddExpression();
                e = std::unique_ptr<Expression>{new ShlExpression(std::move(e), std::move(e1))};
                continue;
            case TOKEN_SHIFTRIGHT:
                // TODO: Advance Token
                this->currentToken = this->lexer.getToken();
                e1 = parseAddExpression();
                e = std::unique_ptr<Expression>{new ShrExpression(std::move(e), std::move(e1))};
                continue;
            
            default:
                break;
        }
        break;
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseEqualityExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseShiftExpression();

    TokenType type = this->currentToken.type;

    switch(this->currentToken.type) {
        case TOKEN_ISEQUAL:
        case TOKEN_NOTEQUAL:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e1 = parseShiftExpression();
            e = std::unique_ptr<Expression>{new EqualityExpression(type, std::move(e), std::move(e1))};
            break;
        case TOKEN_LOWERTHAN:
        case TOKEN_GREATERTHAN:
        case TOKEN_LOWEROREQUALS:
        case TOKEN_GREATEROREQUALS:
            // TODO: Advance Token
            this->currentToken = this->lexer.getToken();
            e1 = parseShiftExpression();
            e = std::unique_ptr<Expression>{new EqualityExpression(type, std::move(e), std::move(e1))};
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
        this->currentToken = this->lexer.getToken();
        e1 = parseEqualityExpression();
        e = std::unique_ptr<Expression>{new AndExpression(std::move(e), std::move(e1))};
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseXorExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseAndExpression();
    while (this->currentToken.type == TOKEN_XOR) {
        //TODO: Advance Token
        this->currentToken = this->lexer.getToken();
        e1 = parseAndExpression();
        e = std::unique_ptr<Expression>{new XorExpression(std::move(e), std::move(e1))};
    }

    return e;
}

std::unique_ptr<Expression> Parser::parseOrExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseXorExpression();
    while (this->currentToken.type == TOKEN_OR) {
        //AdvanceToken
        this->currentToken = this->lexer.getToken();
        e1 = parseXorExpression();
        e = std::unique_ptr<Expression>{new OrExpression(std::move(e), std::move(e1))};
    }
    
    return e;
}

std::unique_ptr<Expression> Parser::parseLogicalAndExpression() {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Expression> e1;

    e = parseOrExpression();
    while (this->currentToken.type == TOKEN_LOGICALAND) {
        //TODO: Advance Token
        this->currentToken = this->lexer.getToken();
        e1 = parseOrExpression();
        e = std::unique_ptr<Expression>{new LogicalAndExpression(std::move(e), std::move(e1))};
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
        this->currentToken = this->lexer.getToken();
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