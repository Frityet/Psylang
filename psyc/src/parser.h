#pragma once

#include <psyc_types.h>

//Replace when lexer implemented
struct Token;
struct Lexer { struct Token *tokens; };

struct Parser {
    struct Token    *tokens;
};

bool parse_tokens(struct Parser *parser, struct Lexer lex);
