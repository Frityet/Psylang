#pragma once

#include <psyc_types.h>

#include "lexer.h"

struct Parser {
    struct Token    *tokens;
};

bool parse_tokens(struct Parser *parser, struct Lexer lex);
