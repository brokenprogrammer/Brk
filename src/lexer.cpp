#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string content) {
    this->content = content;
    this->start = this->content.begin();
    this->end = this->content.end();

    if (this->start != this->end) {
        this->current_char = *this->start;
        this->line = this->read_curr = this->curr = this->start;
        this->line_count = 1;
    }

    this->error_count = 0;
}

Lexer::~Lexer() {

}

Token Lexer::getToken() {
    this->skipWhitespace();

    Token token = {};
    token.str = this->current_char;

    std::string::iterator pos = this->curr;

    if (isLetter(this->current_char)) {
        while(isLetter(this->current_char) || isDigit(this->current_char)) {
            this->tokenizerStep();
        }

        int len = std::distance(this->start, this->curr);
        token.str = std::string(pos, this->curr);

        bool found = false;
        if (len > 1) {
            for (int i = TOKEN_KEYWORDSTART+1; i < TOKEN_KEYWORDSEND; i++) {
                if (token.str.compare(Tokens[i].tokenString) == 0) {
                    token.type = Tokens[i].type;
                    found = true;
                    break;
                }
            }
        }

        // No keyword was found so this must be an identifier.
        if (!found) {
            token.type = TOKEN_IDENTIFIER;
        }


    } else if (isDigit(this->current_char)) {
        token = tokenizerScanNumber();
    } else {
        char current = this->current_char;
        this->tokenizerStep();
        switch(current) {
            case EOF:
                token.type = TOKEN_EOF;
                break;
            case '(':
                token.type = TOKEN_OPENPAREN;
                break;
            case ')':
                token.type = TOKEN_CLOSEPAREN;
                break;
            case '{':
                token.type = TOKEN_OPENBRACE;
                break;
            case '}':
                token.type = TOKEN_CLOSEBRACE;
                break;
            case '[':
                token.type = TOKEN_OPENBRACKET;
                break;
            case ']':
                token.type = TOKEN_CLOSEBRACKET;
                break;
            case '.':
                // TODO: Period have to have some logic to it in the future. - Oskar Mendel 2018-03-19
                token.type = TOKEN_PERIOD;
                break;
            case ',':
                token.type = TOKEN_COMMA;
                break;
            case '?':
                token.type = TOKEN_QUESTION;
                break;
            case ':':
                token.type = TOKEN_COLON;
                break;
            case ';':
                token.type = TOKEN_SEMICOLON;
                break;
            case '\'':
                break;
            case '"':
                // Such faulty implementation, Doesn't support escaped quotes and 
                // doesn't react to non terminated string at the end of line.
                // TODO: Fix whats stated above. - Oskar Mendel 2018-03-19
                token.type = TOKEN_STRING;
                while (this->current_char != '"') {
                    this->tokenizerStep();
                }
                
                token.str = std::string(pos, this->curr+1);
                this->tokenizerStep();

                break;
            case '\\':
                break;
            case '+':
                token.type = TOKEN_ADD;
                if (this->current_char == '+') {
                    token.type = TOKEN_ADDADD;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                } else if (this->current_char == '=') {
                    token.type = TOKEN_ADDEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '-':
                token.type = TOKEN_SUBTRACT;
                if (this->current_char == '-') {
                    token.type = TOKEN_SUBTRACTSUBTRACT;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                } else if (this->current_char == '=') {
                    token.type = TOKEN_SUBTRACTEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '*':
                token.type = TOKEN_MULTIPLY;
                if (this->current_char == '=') {
                    token.type = TOKEN_MULTIPLYEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '/':
                token.type = TOKEN_DIVIDE;
                if (this->current_char == '=') {
                    token.type = TOKEN_DIVIDEEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '%':
                token.type = TOKEN_MOD;
                if (this->current_char == '=') {
                    token.type = TOKEN_MODEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '=':
                token.type = TOKEN_EQUAL;
                if (this->current_char == '=') {
                    token.type = TOKEN_ISEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '!':
                token.type = TOKEN_NOT;
                if (this->current_char == '=') {
                    token.type = TOKEN_NOTEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '#':
                token.type = TOKEN_HASH;
                break;
            case '$':
                token.type = TOKEN_DOLLAR;
                break;
            case '&':
                token.type = TOKEN_AND;
                if (this->current_char == '&') {
                    token.type = TOKEN_LOGICALAND;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                } else if (this->current_char == '=') {
                    token.type = TOKEN_ANDEQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '|':
                token.type = TOKEN_OR;
                if (this->current_char == '|') {
                    token.type = TOKEN_LOGICALOR;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                } else if (this->current_char == '=') {
                    token.type = TOKEN_OREQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '~':
                token.type = TOKEN_XOR;
                if (this->current_char == '=') {
                    token.type = TOKEN_XOREQUAL;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '<':
                token.type = TOKEN_LOWERTHAN;
                if (this->current_char == '<') {
                    token.type = TOKEN_SHIFTLEFT;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                    if (this->current_char == '=') {
                        token.type = TOKEN_SHIFTLEFTEQUAL;
                        this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                    }
                } else if (this->current_char == '=') {
                    token.type = TOKEN_LOWEROREQUALS;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            case '>':
                token.type = TOKEN_GREATERTHAN;
                if (this->current_char == '>') {
                    token.type = TOKEN_SHIFTRIGHT;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                    if (this->current_char == '=') {
                        token.type = TOKEN_SHIFTRIGHTEQUAL;
                        this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                    }
                } else if (this->current_char == '=') {
                    token.type = TOKEN_GREATEROREQUALS;
                    this->tokenizerStep();
                    token.str = std::string(pos, this->curr);
                }
                break;
            default:
                token.type = TOKEN_INVALID;
                break;
        }
    }

    return token;
}

void Lexer::tokenizerStep() {
    if (this->read_curr < this->end) {

        this->curr = this->read_curr;
        if (this->current_char == '\n') {
            this->line = this->curr;
            this->line_count++;
        }
        char c = *this->read_curr;
        if (c == 0) {
            // TODO: Handle Null char. - Oskar Mendel 2018-03-18 
        } else if (c >= 0x80) {
            // TODO: Handle non ascii character. - Oskar Mendel 2018-03-18
        }

        this->read_curr += 1;
        this->current_char = c;

    } else {
        this->curr = this->end;
        if (this->current_char == 'n') {
            this->line = this->curr;
            this->line_count++;
        }

        this->current_char = EOF;
    }
}

// TODO: This is a trash function for scanning numbers, make it more robust when
//  scanning floating points numbers and add support for: binary, hex, octal..
//  Oskar Mendel 2018-03-19
Token Lexer::tokenizerScanNumber() {
    Token token = {};
    token.str = this->current_char;
    token.type = TOKEN_INT32;

    std::string::iterator pos = this->curr;

    char current = this->current_char;
    while(isDigit(current)) {
        this->tokenizerStep();
        if (this->current_char == '.') {
            if (token.type != TOKEN_FLOAT32) {
                token.type = TOKEN_FLOAT32;
                this->tokenizerStep();
                current = this->current_char;
            } else {
                // Multiple dots were found in the number..
            }
        }
        current = this->current_char;
    }

    token.str = std::string(pos, this->curr);

    return token;
}

void Lexer::skipWhitespace() {
    while (this->current_char == ' '  ||
           this->current_char == '\t' ||
           this->current_char == '\n' ||
           this->current_char == '\r') {
        this->tokenizerStep();
    }
}

bool Lexer::isLetter(char c) {
    return isalpha(c);
}

bool Lexer::isDigit(char c) {
    return isdigit(c);
}