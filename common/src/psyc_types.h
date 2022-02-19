//
// Created by Frityet on 2022-02-18.
//

#pragma once

#include <stddef.h>
#include <stdio.h>

#ifdef bool
#undef bool
#undef true
#undef false
#endif

/**
 * @brief C99 Bools really sucks, this is a good replacement
 */
typedef enum bool: _Bool { true = 1, false = 0 } bool;
