//
// Created by Frityet on 2022-02-17.
//

#pragma once

#include "list.h"

/**
 * @brief Generic type defining an automatically deallocating list.
 *
 * @example
 * @code
 * List_tp(int) list = LIST(int);
 * //automatically deallocated!
 * @endcode
 */
#define List_tp(_type) __attribute__((cleanup(autocleanup_list))) _type *

static inline void autocleanup_list(void *list)
{
    free_list(*((void **)list));
}
