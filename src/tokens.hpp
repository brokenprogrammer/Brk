#ifndef BRK_TOKENS_HPP
#define BRK_TOKENS_HPP

#include "types.hpp"
#include "identifier.hpp"
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
    TOKEN_UINT8,
    TOKEN_INT8,
    TOKEN_UINT16,
    TOKEN_INT16,
    TOKEN_UINT32,
    TOKEN_INT32,
    TOKEN_UINT64,
    TOKEN_INT64,
    TOKEN_FLOAT32,
    TOKEN_FLOAT64,
    TOKEN_BYTE,
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
    TOKEN_EXTERN,
    TOKEN_CONST,
    TOKEN_IMPORT,
    TOKEN_AUTO,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_DO,
    TOKEN_SWITCH,
    TOKEN_CASE,
    TOKEN_DEFAULT,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_RETURN,
    TOKEN_KEYWORDSEND
};

struct TokenValue {
    TokenType type;
    const char* tokenString;
} static const Tokens[] {
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

    //TODO: This should also be keywords. Oskar Mendel 2018-04-03
    {TOKEN_LITERALSTART, ""},
    {TOKEN_UINT8, "uint8"},
    {TOKEN_INT8, "int8"},
    {TOKEN_UINT16, "uint16"},
    {TOKEN_INT16, "int16"},
    {TOKEN_UINT32, "uint32"},
    {TOKEN_INT32, "int32"},
    {TOKEN_UINT64, "uint64"},
    {TOKEN_INT64, "int64"},
    {TOKEN_FLOAT32, "float32"},
    {TOKEN_FLOAT64, "float64"},
    {TOKEN_BYTE, "byte"},
    {TOKEN_CHAR, "Char"},
    {TOKEN_STRING, "String"},
    {TOKEN_LITERALEND, ""},

    {TOKEN_OPERATORSTART, ""},
    {TOKEN_ADD, "+"},
    {TOKEN_ADDADD, "++"},
    {TOKEN_SUBTRACT, "-"},
    {TOKEN_SUBTRACTSUBTRACT, "--"},
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
    {TOKEN_LOGICALOR, "||"},
    {TOKEN_LOGICALAND, "&&"},
    {TOKEN_NOTEQUAL, "!="},
    {TOKEN_LOWERTHAN, "<"},
    {TOKEN_GREATERTHAN, ">"},
    {TOKEN_LOWEROREQUALS, "<="},
    {TOKEN_GREATEROREQUALS, ">="},
    {TOKEN_COMPARISONEND, ""},

    {TOKEN_KEYWORDSTART, ""},
    {TOKEN_VOID, "void"},
    /* Aggregates (Struct, class, union.. )*/ //TODO: Oskar Mendel 2018-04-03
    {TOKEN_EXTERN, "extern"},
    {TOKEN_CONST, "const"},
    {TOKEN_IMPORT, "import"},
    {TOKEN_AUTO, "auto"},
    {TOKEN_IF, "if"},
    {TOKEN_ELSE, "else"},
    {TOKEN_WHILE, "while"},
    {TOKEN_FOR, "for"},
    {TOKEN_DO, "do"},
    {TOKEN_SWITCH, "switch"},
    {TOKEN_CASE, "case"},
    {TOKEN_DEFAULT, "default"},
    {TOKEN_BREAK, "break"},
    {TOKEN_CONTINUE, "continue"},
    {TOKEN_RETURN, "return"},
    {TOKEN_KEYWORDSEND, ""}
};

struct Token {
    TokenType type;
    std::string str;
    //TODO: Token Position within file, used for error handling etc.. - Oskar Mendel 2018-03-18

    //TODO: This generates the following warnings:
    //  * Anonymous structs are a GNU extension [-Wgnu-anonymous-struct]
    //  * Anonymous types declared in anonymous union are an extension [-Wnested-anon-types]
    // Is this something that needs fixing or should the warnings be disabled? Oskar Mendel 2018-03-30
    union {
        brk_uint32 uint32Val;
        brk_int32 int32Val;
        brk_uint64 uint64Val;
        brk_int64 int64Val;

        brk_float64 float64Val;

        struct {
            wchar_t *string;
            unsigned length;
        };
    };

    Identifier* identifier;
};

#endif //BRK_TOKENS_HPP