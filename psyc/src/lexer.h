//
// Created by Frityet on 2022-02-22.
//

#pragma once

#include <psyc_types.h>
#include <utilities.h>
#include <wstring.h>

enum TokenType {
    //Mathematical operators
    TOKEN_TYPE_ADD, TOKEN_TYPE_SUB, TOKEN_TYPE_DIV, TOKEN_TYPE_MUL, TOKEN_TYPE_MOD,

    //Boolean operators
    TOKEN_TYPE_EQUALS, TOKEN_TYPE_LESS_THAN, TOKEN_TYPE_GREATER_THAN,
    TOKEN_TYPE_GREATER_THAN_EQUAL_TO, TOKEN_TYPE_LESS_THAN_EQUAL_TO,
    TOKEN_TYPE_NOT, TOKEN_TYPE_AND, TOKEN_TYPE_OR, TOKEN_TYPE_NOT_EQUAL,

    //Grouping symbols
    TOKEN_TYPE_OPEN_PAREN, TOKEN_TYPE_CLOSE_PAREN,
    TOKEN_TYPE_OPEN_CURLY, TOKEN_TYPE_CLOSE_CURLY,
    TOKEN_TYPE_OPEN_SQUARE, TOKEN_TYPE_CLOSE_SQUARE,

    //Keywords
    TOKEN_TYPE_IF, TOKEN_TYPE_ELSE,
    TOKEN_TYPE_REPEAT,
    TOKEN_TYPE_TIMES, TOKEN_TYPE_UNTIL,
    TOKEN_TYPE_PROCEDURE, TOKEN_TYPE_RETURN,

    //Literals
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_STRING, TOKEN_TYPE_NUMBER,

    //Assignment
    TOKEN_TYPE_ASSIGN,

    //End of file
    TOKEN_TYPE_EOF
};

struct Token {
    enum TokenType  type;
    char            *value;
};


struct Lexer {
    struct Token    *tokens;
    WString_t       *src;
};

#define LEXER(...) lexstr((WString_t []){ __VA_ARGS__ }, VA_ARGS_COUNT(__VA_ARGS__))
struct Lexer lexstr(WString_t src[], size_t len);
