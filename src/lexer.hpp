#ifndef BRK_LEXER_HPP
#define BRK_LEXER_HPP

#include "tokens.hpp"
#include <string>

class Lexer {
public:
    Lexer(std::string content);
    Lexer(const Lexer&) = default;
    Lexer& operator=(const Lexer&) = default;
    ~Lexer();

    Token getToken();
private:
    void tokenizerStep();   //TODO: Find a better name for this. - Oskar Mendel 2018-03-18
    Token tokenizerScanNumber();
    Token tokenizerScanRealNumber();
    void skipWhitespace();

    bool isLetter(char c);
    bool isDigit(char c);

    //TODO: Change theese to proper types, uint8 perhaps.. - Oskar Mendel 2018-03-18
    std::string content;
    std::string::iterator start;
    std::string::iterator end;

    char current_char;
    
    std::string::iterator curr;
    std::string::iterator read_curr;
    std::string::iterator line;

    int line_count;
    int error_count;
};

#endif //BRK_LEXER_HPP
