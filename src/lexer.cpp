#include "lexer.hpp"

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


    return token;
}

void Lexer::tokenizerStep() {

}

void Lexer::skipWhitespace() {
    while (this->current_char == ' '  ||
           this->current_char == '\t' ||
           this->current_char == '\n' ||
           this->current_char == '\r') {
        this->tokenizerStep();
    }
}