#include "lexer.hpp"
#include <cctype>
#include <iostream>

Lexer::Lexer(std::string content) {
    this->content = content;
    this->start = this->content.begin();
    this->end = this->content.end();

    if (this->start != this->end) {
        this->current_char = *this->start;
        this->line = this->read_curr = this->curr = this->start;
        this->read_curr += 1;
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
            case '\'': //TODO before moving from lexer. Oskar Mendel 2018-04-03
                break;
            case '"':
                token.type = TOKEN_STRING;
                while (this->current_char != '"') {
                    if (this->current_char == '\n' || this->current_char < 0) {
                        //TODO: Error, string is not terminated. Oskar Mendel 2018-04-03
                    }

                    //TODO: Doesn't check escape sequence within string. Oskar Mendel 2018-04-03
                    this->tokenizerStep();
                }
                
                token.str = std::string(pos, this->curr+1);
                token.string = token.str.c_str();
                token.length = (this->curr+1) - pos;

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

// TODO: Add support for floating point numbers. Oskar Mendel 2018-04-03
Token Lexer::tokenizerScanNumber() {
    Token token = {};
    token.str = this->current_char;
    token.type = TOKEN_INT32;
    int base = 10;
    brk_int64 n = 0;
    int d = 0;

    if (this->current_char == '0') {
        this->tokenizerStep();
        switch (this->current_char) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                n = this->current_char - '0';
                this->tokenizerStep();
                base = 8;
                break;
            case 'x':
            case 'X':
                this->tokenizerStep();
                base = 16;
                break;
            case 'b':
            case 'B':
                this->tokenizerStep();
                base = 2;
                break;
        }
    }

    while (1) {
        switch (this->current_char) {
            case '0':
            case '1':
                d = this->current_char - '0';
                this->tokenizerStep();
                break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                if (base == 2) {
                    //TODO: Error
                }
                d = this->current_char - '0';
                this->tokenizerStep();
                break;
            case '8':
            case '9':
                if (base < 10) {
                    //TODO: Error
                }
                d = this->current_char - '0';
                this->tokenizerStep();
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                if (base != 16) {
                    //TODO: Error
                }

                if (this->current_char >= 'a') {
                    d = this->current_char + 10 - 'a';
                } else {
                    d = this->current_char + 10 - 'A';
                }

                this->tokenizerStep();
                break;
            default:
                goto isDone;
        }

        n = n * base + d;
    }

isDone:
    //Parse trailing flags.. 
    enum FLAGS {
        FLAGS_NONE = 0,
        FLAGS_DECIMAL = 1,
        FLAGS_UNSIGNED = 2,
        FLAGS_LONG = 4
    };

    FLAGS flags = (base == 10) ? FLAGS_DECIMAL : FLAGS_NONE;
    while (1) {
        unsigned char f;
        switch (this->current_char) {
            case 'u':
            case 'U':
                f = FLAGS_UNSIGNED;
                goto L1;
            case 'l':
            case 'L':
                f = FLAGS_LONG;
            L1:
                if (flags & f) {
                    //Error
                }
                flags = (FLAGS)(flags | f);
                this->tokenizerStep();
                continue;
            default:
                break;
        }
        break;
    }

    switch (flags) {
        case FLAGS_NONE:    // Octal or Hex constant.
            if (n & 0x8000000000000000L) {
                token.type = TOKEN_UINT64;
            } else if (n & 0xFFFFFFFF00000000L) {
                token.type = TOKEN_INT64;
            } else if (n & 0x80000000) {
                token.type = TOKEN_UINT32;
            } else {
                token.type = TOKEN_INT32;
            }
            break;
        case FLAGS_DECIMAL:
            if (n & 0x8000000000000000L) {
                //TODO: Error handling
                token.type = TOKEN_UINT64;
            } else if (n & 0xFFFFFFFF00000000L) {
                token.type = TOKEN_INT64;
            } else {
                token.type = TOKEN_INT32;
            }
            break;
        case FLAGS_UNSIGNED:
        case FLAGS_DECIMAL | FLAGS_UNSIGNED:
            if (n & 0xFFFFFFFF00000000L) {
                token.type = TOKEN_UINT64;
            } else {
                token.type = TOKEN_UINT32;
            }
            break;
        case FLAGS_LONG:
        case FLAGS_DECIMAL | FLAGS_LONG:
            if (n & 0x8000000000000000) {
                token.type = TOKEN_UINT64;
            } else {
                token.type = TOKEN_INT64;
            }
            break;
        case FLAGS_UNSIGNED | FLAGS_LONG:
        case FLAGS_DECIMAL | FLAGS_UNSIGNED | FLAGS_LONG:
            token.type = TOKEN_UINT64;
            break;
    }

    token.uint64Val = n;
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