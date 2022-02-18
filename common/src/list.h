//
// Created by Frityet on 2022-02-16.
//

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
//#include <stdio.h>

#include "psyc_types.h"

#define ADDRESS_OF(__VA_ARGS__) ({ __auto_type _tmp = (__VA_ARGS__); &_tmp; })
#define EVAL(_x) _x

//May god forgive me for this
#define _LIST_1(type, ...)                                              new_list(2, sizeof(type), NULL)
#define _LIST_2(type, dtor)                                             new_list(2, sizeof(type), dtor)
#define _LIST_3(type, dtor, count)                                      new_list(count, sizeof(type), dtor)
//#define _LIST_2(type, count)                                        new_list(count, sizeof(type), NULL)
//#define _LIST_3(type, count, dtor)                                  new_list(count, sizeof(type), dtor)
#define _LIST_REDIRECTOR(n, type, dtor_or_count, func, FUNC, ...)   FUNC
#define LIST(...) _LIST_REDIRECTOR(, ##__VA_ARGS__, _LIST_3(__VA_ARGS__), _LIST_2(__VA_ARGS__), _LIST_1(__VA_ARGS__))
//#define ADD_ITEM(_list, _item) ({                                               \
//                                    struct ListData *_ld = dataof_list(_list);  \
//                                    if (_ld->count >= _ld->max - 1) {           \
//                                        if (!grow_list((void **)&_list)) {      \
//                                           NULL;                                \
//                                        } else {                                \
//                                            _ld = dataof_list(_list);           \
//                                        }                                       \
//                                    }                                           \
//                                    _list[_ld->count] = (_item);                \
//                                    _ld->count++;                               \
//                               })

typedef void FreeItem_f(void *);

struct ListData {
    size_t      size, typesize, count, max;
    FreeItem_f  *free_item;
    void        *data;
};

static inline struct ListData *dataof_list(void *ptr)
{
    struct ListData *list = ptr - sizeof(struct ListData);
    return list->data == ptr ? list : NULL;
}

__attribute__((used))
static void *new_list(size_t count, size_t size, FreeItem_f free_item)
{
    size_t total = count * size;
    struct ListData *list = malloc(total + sizeof(struct ListData));
    if (list == NULL) {
        return NULL;
    }
    list->size = total;
    list->typesize = size;
    list->count = 0;
    list->max = count;
    list->free_item = free_item;
    list->data = list + 1;
    return list->data;
}

static inline size_t sizeof_list(void *ptr)
{
    struct ListData *list = dataof_list(ptr);
    return list == NULL ? 0 : list->size;
}

static inline size_t lengthof_list(void *ptr)
{
    struct ListData *list = dataof_list(ptr);
    return list == NULL ? 0 : list->count;
}

static inline size_t typesizeof_list(void *ptr)
{
    struct ListData *list = dataof_list(ptr);
    return list == NULL ? 0 : list->typesize;
}

static inline FreeItem_f *deallocatorof_list(void *ptr)
{
    struct ListData *list = dataof_list(ptr);
    return list == NULL ? NULL : list->free_item;
}

static void free_list(void *ptr)
{
    struct ListData *ld = dataof_list(ptr);
    if (ld == NULL) {
        return;
    }

    FreeItem_f *free_item = ld->free_item;
    if (free_item != NULL) {
        for (size_t i = 0; i < ld->count; ++i) {
            free_item(ptr + (ld->typesize * i));
        }
    }

    free(dataof_list(ptr));
}
__attribute__((used))
static void *grow_list(void **ptr)
{
    struct ListData *list = dataof_list(*ptr);
    if (list == NULL) {
//        fprintf(stderr, "List is null? (arg: %p, ptr: %p, list: %p)\n", ptr, *ptr, list);
        return NULL;
    }

    void *newlist = new_list(list->max * list->max, list->typesize, list->free_item);
    if (newlist == NULL) {
        return NULL;
    }

    /*
    Yes, this ACTUALLY worked
    for (size_t i = 0; i < list->count; ++i) {
        *((uint64_t *)(newlist + i * list->typesize)) = *((uint64_t *)(list->data + i * list->typesize));
    }
    */

    memcpy(newlist, list->data, list->count * list->typesize);
    
    dataof_list(newlist)->count = list->count;

    free_list(list->data);
    list->data = newlist;
    return list->data;
}

__attribute__((used))
static bool push_list(void *arg, void *item)
{
    void **ptr = (void **)arg;
    struct ListData *list = dataof_list(*ptr);
    if (list == NULL) {
//        fprintf(stderr, "List is null?\n(ptr: %p, item: %p, list: %p)\n", *ptr, item, list);
        return false;
    }

    if (list->count + 1 >= list->max) {
//        printf("Growing list (count: %zu, max: %zu)\n", list->count, list->max);
        if ((list = dataof_list(grow_list(&list->data))) == NULL) {
//            fprintf(stderr, "Couldnt grow list?\n(ptr: %p, item: %p, list: %p)\n", *ptr, item, list);
            return false;
        }
//        printf("List grown to (count: %zu, max: %zu)\n", list->count, list->max);
    }

    memcpy(list->data + (list->count * list->typesize), item, list->typesize);
    list->count++;
    *ptr = list->data;
//    printf("Pushed item to list: (ptr: %p, item: %p, count: %zu)\n", *ptr, item, list->count);
    return true;
}
