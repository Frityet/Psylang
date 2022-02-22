//
// Created by Frityet on 2022-02-18.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef bool
#undef bool
#undef true
#undef false
#endif

/**
 * @brief C99 Bools really sucks, this is a good replacement
 */
enum Bool: _Bool { true = 1, false = 0 };
typedef enum Bool   bool;
typedef bool        Bool;
typedef bool        Boolean;

typedef uint32_t    WChar_t;
typedef WChar_t     *WString_t;

static inline size_t wstrlen(WString_t str)
{
    size_t size = 0;
    while (*str)
        str++, size++;
    return size;
}

static inline WString_t wstrdup(WString_t str)
{
    return calloc(wstrlen(str), sizeof(WChar_t));
}

static inline WString_t wstrcpy(WString_t dst, WString_t src)
{
    while (*src)
        *dst = *src++;
    return dst;
}

static inline WString_t wstrcat(WString_t dst, WString_t src)
{
    WString_t str = dst;
    while (*str)
        str++;
    while (*src)
        *str = *src++;
    return dst;
}

static inline int wputs(WString_t str)
{
    while (*str)
        if (putchar((int)*str++) == EOF)
            return EOF;
    return 1;
}

#ifdef PSYC_FORCE_WSTRING_FUNCS
#define strlen  wstrlen
#define strdup  wstrdup
#define strcpy  wstrcpy
#define strcat  wstrcat

#define puts    wputs
#endif
