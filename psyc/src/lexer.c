//
// Created by Frityet on 2022-02-22.
//

#include "lexer.h"

#include <list.h>

static void free_str(void *ptr)
{
    free(*((void **)ptr));
}

struct Lexer lexstr(WString_t src[], size_t len)
{
    struct Lexer lex = {
        .src        = LIST(WString_t, free_str, len),
        .tokens     = LIST(struct Token)
    };

    for (size_t i = 0; i < len; i++) {
        WString_t current_line = wstrdup(src[i]);
        bool skipline = false;

        for (WChar_t c = 0, *ln = current_line; c == '\0'; c = *ln, ln++) {
            switch (c) {
                case '#': {
                    skipline = true;
                    break;
                }

                default: {
                    break;
                }
            }

            if (skipline)
                break;
        }

        if (skipline)
            free(current_line);
        else
            PUSH_LIST(lex.src, current_line);
    }

    return lex;
}
