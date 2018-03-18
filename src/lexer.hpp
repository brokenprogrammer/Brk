#ifndef BRK_LEXER_HPP
#define BRK_LEXER_HPP

#include <string>

enum TokenType {
    TOKEN_EOF,
    TOKEN_INVALID,

    TOKEN_IDENTIFIER,

    TOKEN_OPENPAREN,
    TOKEN_CLOSEPAREN,
    TOKEN_OPENBRACE,
    TOKEN_CLOSEBRACE,

    TOKEN_KEYWORDSTART,
    TOKEN_VOID,
    TOKEN_KEYWORDSEND
};

struct TokenValue {
    TokenType type;
    const char* tokenString;
}

static const Tokens[] {
    {TOKEN_EOF, "EOF"},

    {TOKEN_INVALID, "Invalid"},
    
    {TOKEN_IDENTIFIER, "Identifier"},

    {TOKEN_OPENPAREN, "("},
    {TOKEN_CLOSEPAREN, ")"},
    {TOKEN_OPENBRACE, "{"},
    {TOKEN_CLOSEBRACE, "}"},

    {TOKEN_KEYWORDSTART, ""},
    {TOKEN_VOID, "void"},
    {TOKEN_KEYWORDSEND, ""}
};

struct Token {
    TokenType type;
    std::string str;
    //TODO: Token Position within file, used for error handling etc.. - Oskar Mendel 2018-03-18
};

class Lexer {
    public:
        Lexer(std::string content);
        Lexer(const Lexer&) = default;
        Lexer& operator=(const Lexer&) = default;
        ~Lexer();

        Token getToken();
    private:
        void tokenizerStep();   //TODO: Find a better name for this. - Oskar Mendel 2018-03-18
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
