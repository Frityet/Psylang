//
// Created by Frityet on 2022-02-17.
//

#pragma once

#include "list.h"

//#if !__has_feature(cleanup)
//#error Managed lists requires the cleanup attribute present in GCC/Clang!
//#endif

#define List_tp(_type) __attribute__((cleanup(autocleanup_list))) _type *

static inline void autocleanup_list(void *list)
{
    free_list(*((void **)list));
}
