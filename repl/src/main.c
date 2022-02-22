//
// Created by Frityet on 2022-02-15.
//

#include <stdio.h>
#define PSYC_FORCE_WSTRING_FUNCS
#include <lexer.h>
#include <managed_list.h>

void free_str(void *ptr)
{
    free(*((void **)ptr));
}

int main()
{
//    struct Lexer lex = lexstr((char *[]) {
//        "DISPLAY(\"HELLO, WORLD!\")",
//        "FOR i IN list",
//        "{",
//        "\t\tDISPLAY(i)",
//        "}"
//    }, 5);
    struct Lexer lex = LEXER(U"DISPLAY(\"HELLO, WORLD!\")", U"DISPLAY(\"GOODBYE, WORLD!\")");
    size_t len = lengthof_list(lex.src);
    for (size_t i = 0; i < len; ++i) {
        puts(lex.src[i]);
    }
}
