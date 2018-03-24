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
    TOKEN_OPENBRACKET,
    TOKEN_CLOSEBRACKET,
    TOKEN_PERIOD,
    TOKEN_COMMA,
    TOKEN_QUESTION,
    TOKEN_COLON,
    TOKEN_SEMICOLON,

    TOKEN_LITERALSTART,
    TOKEN_INTEGER,
    TOKEN_FLOATING,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_LITERALEND,

    TOKEN_OPERATORSTART,
    TOKEN_ADD,
    TOKEN_ADDADD,
    TOKEN_SUBTRACT,
    TOKEN_SUBTRACTSUBTRACT,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MOD,
    TOKEN_EQUAL,
    TOKEN_NOT,
    TOKEN_HASH,
    TOKEN_DOLLAR,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_XOR,
    TOKEN_SHIFTLEFT,
    TOKEN_SHIFTRIGHT,
    TOKEN_OPERATOREND,

    TOKEN_ASSIGNOPERATORSTART,
    TOKEN_ADDEQUAL,
    TOKEN_SUBTRACTEQUAL,
    TOKEN_MULTIPLYEQUAL,
    TOKEN_DIVIDEEQUAL,
    TOKEN_MODEQUAL,
    TOKEN_ANDEQUAL,
    TOKEN_OREQUAL,
    TOKEN_XOREQUAL,
    TOKEN_SHIFTLEFTEQUAL,
    TOKEN_SHIFTRIGHTEQUAL,
    TOKEN_ASSIGNOPERATOREND,

    TOKEN_COMPARISONSTART,
    TOKEN_ISEQUAL,
    TOKEN_LOGICALOR,
    TOKEN_LOGICALAND,
    TOKEN_NOTEQUAL,
    TOKEN_LOWERTHAN,
    TOKEN_GREATERTHAN,
    TOKEN_LOWEROREQUALS,
    TOKEN_GREATEROREQUALS,
    TOKEN_COMPARISONEND,

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
    {TOKEN_OPENBRACKET, "["},
    {TOKEN_CLOSEBRACKET, "]"},
    {TOKEN_PERIOD, "."},
    {TOKEN_COMMA, ","},
    {TOKEN_QUESTION, "?"},
    {TOKEN_COLON, ":"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_LITERALSTART, ""},
    {TOKEN_INTEGER, "Integer"},
    {TOKEN_FLOATING, "Floating"},
    {TOKEN_CHAR, "Char"},
    {TOKEN_STRING, "String"},
    {TOKEN_LITERALEND, ""},

    {TOKEN_OPERATORSTART, ""},
    {TOKEN_ADD, "+"},
    {TOKEN_ADDADD, "++"}, // TODO: Not being lexed yet.. Oskar Mendel 2018-03-24
    {TOKEN_SUBTRACT, "-"},
    {TOKEN_SUBTRACTSUBTRACT, "--"}, // TODO: Not being lexed yet.. Oskar Mendel 2018-03-24
    {TOKEN_MULTIPLY, "*"},
    {TOKEN_DIVIDE, "/"},
    {TOKEN_MOD, "%"},
    {TOKEN_EQUAL, "="},
    {TOKEN_NOT, "!"},
    {TOKEN_HASH, "#"},
    {TOKEN_DOLLAR, "$"},
    {TOKEN_AND, "&"},
    {TOKEN_OR, "|"},
    {TOKEN_XOR, "~"},
    {TOKEN_SHIFTLEFT, "<<"},
    {TOKEN_SHIFTRIGHT, ">>"},
    {TOKEN_OPERATOREND, ""},

    {TOKEN_ASSIGNOPERATORSTART, ""},
    {TOKEN_ADDEQUAL, "+="},
    {TOKEN_SUBTRACTEQUAL, "-="},
    {TOKEN_MULTIPLYEQUAL, "*="},
    {TOKEN_DIVIDEEQUAL, "/="},
    {TOKEN_MODEQUAL, "%="},
    {TOKEN_ANDEQUAL, "&="},
    {TOKEN_OREQUAL, "|="},
    {TOKEN_XOREQUAL, "~="},
    {TOKEN_SHIFTLEFTEQUAL, "<<="},
    {TOKEN_SHIFTRIGHTEQUAL, ">>="},
    {TOKEN_ASSIGNOPERATOREND, ""},

    {TOKEN_COMPARISONSTART, ""},
    {TOKEN_ISEQUAL, "=="},
    {TOKEN_LOGICALOR, "||"}, // TODO: Not being lexed yet.. Oskar Mendel 2018-03-24
    {TOKEN_LOGICALAND, "&&"}, // TODO: Not being lexed yet.. Oskar Mendel 2018-03-24
    {TOKEN_NOTEQUAL, "!="},
    {TOKEN_LOWERTHAN, "<"},
    {TOKEN_GREATERTHAN, ">"},
    {TOKEN_LOWEROREQUALS, "<="},
    {TOKEN_GREATEROREQUALS, ">="},
    {TOKEN_COMPARISONEND, ""},

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
    Token tokenizerScanNumber();
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
