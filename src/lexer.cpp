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
        // TODO: Get keyword out of read chars. - Oskar Mendel 2018-03-18
        int len = std::distance(this->start, this->curr);
        token.str = std::string(pos, this->curr);

        if (len > 1) {
            bool found = false;
            for (int i = TOKEN_KEYWORDSTART+1; i < TOKEN_KEYWORDSEND; i++) {
                if (token.str.compare(Tokens[i].tokenString) == 0) {
                    token.type = Tokens[i].type;
                    found = true;
                    break;
                }
            }

            if (!found) {
                token.type = TOKEN_IDENTIFIER;
            }
            //TODO: Loop through all known keywords and if
                // Found matching keyword then this token is of that
                // keyword.. - Oskar Mendel 2018-03-18
        }


    } else if (false) {//isNumber(this->current_char)) {
        // TODO: Number to token. - Oskar Mendel 2018-03-18
    } else {
        //TODO: Switch on keywords such as '#' '?' ';'.. - Oskar Mendel 2018-03-18
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