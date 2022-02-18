#pragma once

#include <stdint.h>
#include <stddef.h>

struct Token; //Replace when lexer implemented

struct Parser {
    struct Token    *tokens;
    size_t          token_count;
};

